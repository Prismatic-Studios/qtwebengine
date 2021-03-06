/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtWebEngine module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#if defined(USE_OZONE)
#include "surface_factory_qt.h"

#include "ozone/gl_context_qt.h"
#include "ozone/gl_ozone_egl_qt.h"
#if defined(USE_GLX)
#include "ozone/gl_ozone_glx_qt.h"
#endif

namespace QtWebEngineCore {

SurfaceFactoryQt::SurfaceFactoryQt()
{
#if defined(USE_GLX)
    if (GLContextHelper::getGlxPlatformInterface()) {
        m_impl = { gl::GLImplementationParts(gl::kGLImplementationDesktopGL),
                   gl::GLImplementationParts(gl::kGLImplementationDisabled) };
        m_ozone.reset(new ui::GLOzoneGLXQt());
    } else
#endif
    if (GLContextHelper::getEglPlatformInterface()) {
        m_impl = { gl::GLImplementationParts(gl::kGLImplementationDesktopGL),
                   gl::GLImplementationParts(gl::kGLImplementationEGLGLES2),
                   gl::GLImplementationParts(gl::kGLImplementationDisabled) };
        m_ozone.reset(new ui::GLOzoneEGLQt());
    } else {
        qWarning("No suitable graphics backend found\n");
        m_impl = { gl::GLImplementationParts(gl::kGLImplementationDisabled) };
    }
}

std::vector<gl::GLImplementationParts> SurfaceFactoryQt::GetAllowedGLImplementations()
{
    return m_impl;
}

ui::GLOzone *SurfaceFactoryQt::GetGLOzone(const gl::GLImplementationParts &implementation)
{
    return m_ozone.get();
}

} // namespace QtWebEngineCore
#endif // defined(USE_OZONE)

