/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtWebEngine module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL-EXCEPT$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick
import QtTest
import QtWebEngine

TestWebEngineView {
    id: webEngineView
    width: 400
    height: 300


    SignalSpy {
        id: spyTitle
        target: webEngineView
        signalName: "titleChanged"
    }


    TestCase {
        name: "WebEngineViewTitleChangedSignal"

        function test_titleFirstLoad() {
            compare(spyTitle.count, 0)

            var testUrl = Qt.resolvedUrl("test3.html")
            webEngineView.url = testUrl
            spyTitle.wait()
            if (webEngineView.title == "test3.html") {
                // This title may be emitted during loading
                spyTitle.clear()
                spyTitle.wait()
            }
            compare(webEngineView.title, "Test page 3")
            spyTitle.clear()
            spyTitle.wait()
            compare(webEngineView.title, "New Title")
        }
    }
}
