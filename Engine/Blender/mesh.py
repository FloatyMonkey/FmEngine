# Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
# Licensed under the GPL license. See LICENSE.md for full terms. This notice is not to be removed.

import bpy

import struct

from collections import namedtuple

class Vertex:

    def __init__(self, mesh, loop):

        self.position = mesh.vertices[loop.vertex_index].co[:]

        self.normal = loop.normal[:]
        self.tangent = loop.tangent[:]
        self.bitangent = loop.bitangent[:]

        self.texcoords = tuple(
            layer.data[loop.index].uv[:]
            for layer in mesh.uv_layers
            if layer.data
        )

        self.colors = tuple(
            layer.data[loop.index].color[:]
            for layer in mesh.vertex_colors
            if layer.data
        )

    def __hash__(self):
        return hash((self.position, self.normal, self.texcoords, self.colors))

SubMesh = namedtuple('SubMesh', 'offset,count')

def convert_mesh(mesh):
    
    submesh_count = max(1, len(mesh.materials))
    index_buffers = [[] for i in range(submesh_count)]

    vertices = []
    indices = []
    submeshes = []

    v_to_i = {}

    for polygon in mesh.polygons:

        for i in polygon.loop_indices:
            vertex = Vertex(mesh, mesh.loops[i])

            if hash(vertex) not in v_to_i:
                v_to_i[hash(vertex)] = len(vertices)
                vertices.append(vertex)

            index_buffers[polygon.material_index].append(v_to_i[hash(vertex)])

    for buffer in index_buffers:
        submeshes.append(SubMesh(len(indices), len(buffer)))
        indices.extend(buffer)

    return vertices, indices, submeshes

def save_mesh(file, mesh):

    mesh.calc_tangents()
    mesh.calc_normals_split()

    vertices, indices, submeshes = convert_mesh(mesh)

    file.write(struct.pack('<I', len(submeshes)))
    file.write(struct.pack('<I', len(vertices)))
    file.write(struct.pack('<I', len(indices)))

    for submesh in submeshes:
        file.write(struct.pack('<I', submesh.offset))
        file.write(struct.pack('<I', submesh.count))

    for vertex in vertices:
        file.write(struct.pack('<3f', *vertex.position))
        file.write(struct.pack('<3f', *vertex.normal))
        file.write(struct.pack('<2f', *vertex.texcoords[0]))

    for index in indices:
        file.write(struct.pack('<I', index))

def save_fme(context, filepath = ""):

    file = open(filepath, "wb")

    bpy.ops.object.duplicate()
    bpy.ops.object.mode_set(mode="OBJECT")

    for modifier in context.active_object.modifiers:
        bpy.ops.object.modifier_apply(modifier=modifier.name)

    bpy.ops.object.modifier_add(type="TRIANGULATE")
    bpy.ops.object.modifier_apply(apply_as = "DATA", modifier = "Triangulate")
    
    save_mesh(file, context.active_object.to_mesh())

    bpy.ops.object.delete()

    file.close()
