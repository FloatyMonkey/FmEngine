# Copyright (c) 2020 Lauro Oyen, FmEngine contributors. All rights reserved.
# Licensed under the GPL license. See LICENSE.md for full terms. This notice is not to be removed.

bl_info = {
    "name" : "FmEngine",
    "category" : "Game Engine",
    "description" : "3D Game Engine",
    "author" : "Lauro Oyen, FmEngine contributors",
    "blender" : (2, 81, 0),
    "version" : (0, 0, 1),
}

import bpy
from bpy.props import *
from bpy_extras.io_utils import ExportHelper

from .mesh import save_fme

class ExportFmEngine(bpy.types.Operator, ExportHelper):
    bl_idname = "export.fme"
    bl_label = "Export FmEngine"
    filename_ext = ".fme"
    
    def invoke(self, context, event):
        return ExportHelper.invoke(self, context, event)
    
    @classmethod
    def poll(cls, context):
        return context.active_object != None
    
    def execute(self, context):
        save_fme(context, self.filepath)
        return {"FINISHED"}

def add_to_menu(self, context):
    self.layout.operator(ExportFmEngine.bl_idname, text="FmEngine (.fme)")

def register():
    bpy.utils.register_class(ExportFmEngine)
    bpy.types.TOPBAR_MT_file_export.append(add_to_menu)

def unregister():
    bpy.types.TOPBAR_MT_file_export.remove(add_to_menu)
    bpy.utils.unregister_class(ExportFmEngine)
