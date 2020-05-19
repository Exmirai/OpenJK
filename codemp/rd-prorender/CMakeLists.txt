#============================================================================
# Copyright (C) 2013 - 2018, OpenJK contributors
#
# This file is part of the OpenJK source code.
#
# OpenJK is free software; you can redistribute it and/or modify it
# under the terms of the GNU General Public License version 2 as
# published by the Free Software Foundation.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, see <http://www.gnu.org/licenses/>.
#============================================================================

# Make sure the user is not executing this script directly
if(NOT InOpenJK)
	message(FATAL_ERROR "Use the top-level cmake script!")
endif(NOT InOpenJK)

# Check for dependencies first

set(MPRadeonRendererIncludeDirectories ${MPDir})
set(MPRadeonRendererIncludeDirectories
	${MRadeonRendererIncludeDirectories}
	${SharedDir}
	${MPDir}
	"${MPDir}/rd-prorender"
	"${GSLIncludeDirectory}"
	)

set(MPRadeonRendererFiles
	"${MPDir}/rd-prorender/glext.h"
	"${MPDir}/rd-prorender/qgl.h"
	"${MPDir}/rd-prorender/G2_API.cpp"
	"${MPDir}/rd-prorender/G2_bolts.cpp"
	"${MPDir}/rd-prorender/G2_bones.cpp"
	"${MPDir}/rd-prorender/G2_misc.cpp"
	"${MPDir}/rd-prorender/G2_surfaces.cpp"
	"${MPDir}/rd-prorender/tr_arb.cpp"
	"${MPDir}/rd-prorender/tr_backend.cpp"
	"${MPDir}/rd-prorender/tr_bsp.cpp"
	"${MPDir}/rd-prorender/tr_cmds.cpp"
	"${MPDir}/rd-prorender/tr_curve.cpp"
	"${MPDir}/rd-prorender/tr_decals.cpp"
	"${MPDir}/rd-prorender/tr_ghoul2.cpp"
	"${MPDir}/rd-prorender/tr_image.cpp"
	"${MPDir}/rd-prorender/tr_init.cpp"
	"${MPDir}/rd-prorender/tr_light.cpp"
	"${MPDir}/rd-prorender/tr_local.h"
	"${MPDir}/rd-prorender/tr_main.cpp"
	"${MPDir}/rd-prorender/tr_marks.cpp"
	"${MPDir}/rd-prorender/tr_mesh.cpp"
	"${MPDir}/rd-prorender/tr_model.cpp"
	"${MPDir}/rd-prorender/tr_quicksprite.cpp"
	"${MPDir}/rd-prorender/tr_quicksprite.h"
	"${MPDir}/rd-prorender/tr_scene.cpp"
	"${MPDir}/rd-prorender/tr_shade.cpp"
	"${MPDir}/rd-prorender/tr_shade_calc.cpp"
	"${MPDir}/rd-prorender/tr_shader.cpp"
	"${MPDir}/rd-prorender/tr_shadows.cpp"
	"${MPDir}/rd-prorender/tr_skin.cpp"
	"${MPDir}/rd-prorender/tr_sky.cpp"
	"${MPDir}/rd-prorender/tr_subs.cpp"
	"${MPDir}/rd-prorender/tr_surface.cpp"
	"${MPDir}/rd-prorender/tr_surfacesprites.cpp"
	"${MPDir}/rd-prorender/tr_world.cpp"
	"${MPDir}/rd-prorender/tr_WorldEffects.cpp"
	"${MPDir}/rd-prorender/tr_WorldEffects.h"
	)
source_group("renderer" FILES ${MPRadeonRendererFiles})

set(MPRadeonRendererGhoul2Files
	"${MPDir}/ghoul2/g2_local.h"
	"${MPDir}/ghoul2/ghoul2_shared.h"
	"${MPDir}/ghoul2/G2_gore.cpp"
	"${MPDir}/ghoul2/G2_gore.h")
source_group("ghoul2" FILES ${MPRadeonRendererGhoul2Files})
set(MPRadeonRendererFiles ${MPRadeonRendererFiles} ${MPRadeonRendererGhoul2Files})

set(MPRadeonRendererRdCommonFiles
	"${MPDir}/rd-common/mdx_format.h"
	"${MPDir}/rd-common/tr_common.h"
	"${MPDir}/rd-common/tr_font.cpp"
	"${MPDir}/rd-common/tr_font.h"
	"${MPDir}/rd-common/tr_image_load.cpp"
	"${MPDir}/rd-common/tr_image_jpg.cpp"
	"${MPDir}/rd-common/tr_image_tga.cpp"
	"${MPDir}/rd-common/tr_image_png.cpp"
	"${MPDir}/rd-common/tr_noise.cpp"
	"${MPDir}/rd-common/tr_public.h"
	"${MPDir}/rd-common/tr_types.h")
source_group("rd-common" FILES ${MPRadeonRendererRdCommonFiles})
set(MPRadeonRendererFiles ${MPRadeonRendererFiles} ${MPRadeonRendererRdCommonFiles})

set(MPRadeonRendererCommonFiles
	"${MPDir}/qcommon/matcomp.cpp"
	"${MPDir}/qcommon/q_shared.cpp"
	
	${SharedCommonFiles})
source_group("common" FILES ${MPRadeonRendererCommonFiles})
set(MPRadeonRendererFiles ${MPRadeonRendererFiles} ${MPRadeonRendererCommonFiles})

set(MPRadeonRendererCommonSafeFiles
	${SharedCommonSafeFiles}
	)
source_group("common/safe" FILES ${MPRadeonRendererCommonSafeFiles})
set(MPRadeonRendererFiles ${MPRadeonRendererFiles} ${MPRadeonRendererCommonSafeFiles})

# Transparently use either bundled or system libjpeg.
list(APPEND MPRadeonRendererIncludeDirectories ${JPEG_INCLUDE_DIR})
list(APPEND MPRadeonRendererLibraries          ${JPEG_LIBRARIES})

# Transparently use either bundled or system libpng.  Order is important --
# libpng used zlib, so it must come before it on the linker command line.
list(APPEND MPRadeonRendererIncludeDirectories ${PNG_INCLUDE_DIRS})
list(APPEND MPRadeonRendererLibraries          ${PNG_LIBRARIES})

# Transparently use either bundled or system zlib.
list(APPEND MPRadeonRendererIncludeDirectories ${ZLIB_INCLUDE_DIR})
list(APPEND MPRadeonRendererLibraries          ${ZLIB_LIBRARIES})

# Transparently use our bundled minizip.
list(APPEND MPRadeonRendererIncludeDirectories ${MINIZIP_INCLUDE_DIRS})
list(APPEND MPRadeonRendererLibraries          ${MINIZIP_LIBRARIES})

find_package(OpenGL REQUIRED)
set(MPRadeonRendererIncludeDirectories ${MPRadeonRendererIncludeDirectories} ${OPENGL_INCLUDE_DIR})
set(MPRadeonRendererLibraries ${MPRadeonRendererLibraries} ${OPENGL_LIBRARIES})

set(MPRadeonRendererIncludeDirectories ${MPRadeonRendererIncludeDirectories} ${OpenJKLibDir})
add_library(${MPRadeonRenderer} SHARED ${MPRadeonRendererFiles})

if(NOT MSVC)
	# remove "lib" prefix for .so/.dylib files
	set_target_properties(${MPRadeonRenderer} PROPERTIES PREFIX "")
endif()

if(WIN32)
	install(TARGETS ${MPRadeonRenderer}
		RUNTIME
		DESTINATION ${JKAInstallDir}
		COMPONENT ${JKAMPClientComponent})
else(WIN32)
	if(MakeApplicationBundles AND BuildMPEngine)
		install(TARGETS ${MPRadeonRenderer}
			LIBRARY
			DESTINATION "${JKAInstallDir}/${MPEngine}.app/Contents/MacOS/"
			COMPONENT ${JKAMPClientComponent})
	else()
		install(TARGETS ${MPRadeonRenderer}
			LIBRARY
			DESTINATION ${JKAInstallDir}
			COMPONENT ${JKAMPClientComponent})
	endif()
endif()

set_target_properties(${MPRadeonRenderer} PROPERTIES COMPILE_DEFINITIONS "${SharedDefines}")

# Hide symbols not explicitly marked public.
set_property(TARGET ${MPRadeonRenderer} APPEND PROPERTY COMPILE_OPTIONS ${OPENJK_VISIBILITY_FLAGS})

set_target_properties(${MPRadeonRenderer} PROPERTIES INCLUDE_DIRECTORIES "${MPRadeonRendererIncludeDirectories}")
set_target_properties(${MPRadeonRenderer} PROPERTIES PROJECT_LABEL "MP Radeon Renderer")
target_link_libraries(${MPRadeonRenderer} ${MPRadeonRendererLibraries})
