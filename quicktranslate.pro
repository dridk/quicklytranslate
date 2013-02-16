QT += network script phonon

win32:RC_FILE = myapp.rc
mac:ICONS = resources/icon.png

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    preferencedialog.cpp \
    textedit.cpp \
    languagemodel.cpp \
    aboutdialog.cpp \
    ttsdialog.cpp \
    qxtjson/qxtjson.cpp \

HEADERS += \
    mainwindow.h \
    preferencedialog.h \
    textedit.h \
    languagemodel.h \
    aboutdialog.h \
   ttsdialog.h \
    qxtjson/qxtjson.h \

FORMS += \
    mainwindow.ui \
    preferencedialog.ui \
    aboutdialog.ui \
    ttsdialog.ui

RESOURCES += \
    resources/resources.qrc \
    resources/icons.qrc

TRANSLATIONS = quicklytranslate_fr.ts

OTHER_FILES += \
    myapp.rc
