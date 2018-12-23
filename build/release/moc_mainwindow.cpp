/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../cmini/src/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[87];
    char stringdata0[1888];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 4), // "save"
QT_MOC_LITERAL(2, 16, 0), // ""
QT_MOC_LITERAL(3, 17, 4), // "open"
QT_MOC_LITERAL(4, 22, 4), // "file"
QT_MOC_LITERAL(5, 27, 6), // "newTab"
QT_MOC_LITERAL(6, 34, 10), // "selectText"
QT_MOC_LITERAL(7, 45, 3), // "pos"
QT_MOC_LITERAL(8, 49, 3), // "len"
QT_MOC_LITERAL(9, 53, 20), // "highlightCurrentLine"
QT_MOC_LITERAL(10, 74, 22), // "updateHighlighterTheme"
QT_MOC_LITERAL(11, 97, 11), // "setTabWidth"
QT_MOC_LITERAL(12, 109, 5), // "width"
QT_MOC_LITERAL(13, 115, 14), // "updateLineNums"
QT_MOC_LITERAL(14, 130, 13), // "newBlockCount"
QT_MOC_LITERAL(15, 144, 14), // "scrollOverview"
QT_MOC_LITERAL(16, 159, 11), // "scrollValue"
QT_MOC_LITERAL(17, 171, 18), // "setMainWindowStyle"
QT_MOC_LITERAL(18, 190, 15), // "backgroundColor"
QT_MOC_LITERAL(19, 206, 9), // "lineColor"
QT_MOC_LITERAL(20, 216, 17), // "setTabWidgetStyle"
QT_MOC_LITERAL(21, 234, 15), // "foregroundColor"
QT_MOC_LITERAL(22, 250, 15), // "setLineNumStyle"
QT_MOC_LITERAL(23, 266, 16), // "setOverViewStyle"
QT_MOC_LITERAL(24, 283, 11), // "getFileType"
QT_MOC_LITERAL(25, 295, 23), // "on_actionOpen_triggered"
QT_MOC_LITERAL(26, 319, 22), // "on_actionNew_triggered"
QT_MOC_LITERAL(27, 342, 23), // "on_actionSave_triggered"
QT_MOC_LITERAL(28, 366, 23), // "on_actionUndo_triggered"
QT_MOC_LITERAL(29, 390, 23), // "on_actionRedo_triggered"
QT_MOC_LITERAL(30, 414, 23), // "on_actionExit_triggered"
QT_MOC_LITERAL(31, 438, 26), // "on_actionSave_as_triggered"
QT_MOC_LITERAL(32, 465, 23), // "on_actionFind_triggered"
QT_MOC_LITERAL(33, 489, 22), // "on_actionHex_triggered"
QT_MOC_LITERAL(34, 512, 24), // "on_actionAscii_triggered"
QT_MOC_LITERAL(35, 537, 26), // "on_actionStrings_triggered"
QT_MOC_LITERAL(36, 564, 29), // "on_findLineEdit_returnPressed"
QT_MOC_LITERAL(37, 594, 24), // "on_actionAbout_triggered"
QT_MOC_LITERAL(38, 619, 30), // "on_tabWidget_tabCloseRequested"
QT_MOC_LITERAL(39, 650, 5), // "index"
QT_MOC_LITERAL(40, 656, 27), // "on_tabWidget_currentChanged"
QT_MOC_LITERAL(41, 684, 19), // "onBlockCountChanged"
QT_MOC_LITERAL(42, 704, 13), // "onTextChanged"
QT_MOC_LITERAL(43, 718, 29), // "on_actionFullScreen_triggered"
QT_MOC_LITERAL(44, 748, 23), // "on_actionGoTo_triggered"
QT_MOC_LITERAL(45, 772, 22), // "on_actionAsm_triggered"
QT_MOC_LITERAL(46, 795, 20), // "on_actionC_triggered"
QT_MOC_LITERAL(47, 816, 29), // "on_actionCpluspluss_triggered"
QT_MOC_LITERAL(48, 846, 23), // "on_actionHtml_triggered"
QT_MOC_LITERAL(49, 870, 23), // "on_actionJava_triggered"
QT_MOC_LITERAL(50, 894, 20), // "confirmApplyTemplate"
QT_MOC_LITERAL(51, 915, 22), // "on_actionCss_triggered"
QT_MOC_LITERAL(52, 938, 21), // "on_findButton_clicked"
QT_MOC_LITERAL(53, 960, 25), // "on_findPrevButton_clicked"
QT_MOC_LITERAL(54, 986, 28), // "on_actionFind_Next_triggered"
QT_MOC_LITERAL(55, 1015, 8), // "findNext"
QT_MOC_LITERAL(56, 1024, 8), // "findPrev"
QT_MOC_LITERAL(57, 1033, 32), // "on_actionFind_Previous_triggered"
QT_MOC_LITERAL(58, 1066, 26), // "on_actionReplace_triggered"
QT_MOC_LITERAL(59, 1093, 24), // "on_replaceButton_clicked"
QT_MOC_LITERAL(60, 1118, 30), // "on_actionDelete_line_triggered"
QT_MOC_LITERAL(61, 1149, 30), // "on_actionRemove_word_triggered"
QT_MOC_LITERAL(62, 1180, 27), // "on_replaceAllButton_clicked"
QT_MOC_LITERAL(63, 1208, 32), // "on_replaceLineEdit_returnPressed"
QT_MOC_LITERAL(64, 1241, 27), // "on_findLineEdit_textChanged"
QT_MOC_LITERAL(65, 1269, 4), // "arg1"
QT_MOC_LITERAL(66, 1274, 33), // "on_actionToggle_comment_trigg..."
QT_MOC_LITERAL(67, 1308, 27), // "on_actionOverview_triggered"
QT_MOC_LITERAL(68, 1336, 23), // "on_actionDark_triggered"
QT_MOC_LITERAL(69, 1360, 33), // "on_actionSolarized_Dark_trigg..."
QT_MOC_LITERAL(70, 1394, 29), // "on_actionJoin_Lines_triggered"
QT_MOC_LITERAL(71, 1424, 31), // "on_actionMove_Line_Up_triggered"
QT_MOC_LITERAL(72, 1456, 33), // "on_actionSwap_line_down_trigg..."
QT_MOC_LITERAL(73, 1490, 26), // "on_actionMenubar_triggered"
QT_MOC_LITERAL(74, 1517, 28), // "on_actionSolarized_triggered"
QT_MOC_LITERAL(75, 1546, 20), // "on_action8_triggered"
QT_MOC_LITERAL(76, 1567, 20), // "on_action4_triggered"
QT_MOC_LITERAL(77, 1588, 20), // "on_action2_triggered"
QT_MOC_LITERAL(78, 1609, 28), // "on_actionClose_All_triggered"
QT_MOC_LITERAL(79, 1638, 28), // "on_actionTommorrow_triggered"
QT_MOC_LITERAL(80, 1667, 34), // "on_actionTommorrow_Night_trig..."
QT_MOC_LITERAL(81, 1702, 29), // "on_actionRunIn16Bit_triggered"
QT_MOC_LITERAL(82, 1732, 29), // "on_actionRunIn64Bit_triggered"
QT_MOC_LITERAL(83, 1762, 30), // "on_actionToken_Table_triggered"
QT_MOC_LITERAL(84, 1793, 31), // "on_actionSymbol_Table_triggered"
QT_MOC_LITERAL(85, 1825, 34), // "on_actionQuaternary_File_trig..."
QT_MOC_LITERAL(86, 1860, 27) // "on_actionASM_File_triggered"

    },
    "MainWindow\0save\0\0open\0file\0newTab\0"
    "selectText\0pos\0len\0highlightCurrentLine\0"
    "updateHighlighterTheme\0setTabWidth\0"
    "width\0updateLineNums\0newBlockCount\0"
    "scrollOverview\0scrollValue\0"
    "setMainWindowStyle\0backgroundColor\0"
    "lineColor\0setTabWidgetStyle\0foregroundColor\0"
    "setLineNumStyle\0setOverViewStyle\0"
    "getFileType\0on_actionOpen_triggered\0"
    "on_actionNew_triggered\0on_actionSave_triggered\0"
    "on_actionUndo_triggered\0on_actionRedo_triggered\0"
    "on_actionExit_triggered\0"
    "on_actionSave_as_triggered\0"
    "on_actionFind_triggered\0on_actionHex_triggered\0"
    "on_actionAscii_triggered\0"
    "on_actionStrings_triggered\0"
    "on_findLineEdit_returnPressed\0"
    "on_actionAbout_triggered\0"
    "on_tabWidget_tabCloseRequested\0index\0"
    "on_tabWidget_currentChanged\0"
    "onBlockCountChanged\0onTextChanged\0"
    "on_actionFullScreen_triggered\0"
    "on_actionGoTo_triggered\0on_actionAsm_triggered\0"
    "on_actionC_triggered\0on_actionCpluspluss_triggered\0"
    "on_actionHtml_triggered\0on_actionJava_triggered\0"
    "confirmApplyTemplate\0on_actionCss_triggered\0"
    "on_findButton_clicked\0on_findPrevButton_clicked\0"
    "on_actionFind_Next_triggered\0findNext\0"
    "findPrev\0on_actionFind_Previous_triggered\0"
    "on_actionReplace_triggered\0"
    "on_replaceButton_clicked\0"
    "on_actionDelete_line_triggered\0"
    "on_actionRemove_word_triggered\0"
    "on_replaceAllButton_clicked\0"
    "on_replaceLineEdit_returnPressed\0"
    "on_findLineEdit_textChanged\0arg1\0"
    "on_actionToggle_comment_triggered\0"
    "on_actionOverview_triggered\0"
    "on_actionDark_triggered\0"
    "on_actionSolarized_Dark_triggered\0"
    "on_actionJoin_Lines_triggered\0"
    "on_actionMove_Line_Up_triggered\0"
    "on_actionSwap_line_down_triggered\0"
    "on_actionMenubar_triggered\0"
    "on_actionSolarized_triggered\0"
    "on_action8_triggered\0on_action4_triggered\0"
    "on_action2_triggered\0on_actionClose_All_triggered\0"
    "on_actionTommorrow_triggered\0"
    "on_actionTommorrow_Night_triggered\0"
    "on_actionRunIn16Bit_triggered\0"
    "on_actionRunIn64Bit_triggered\0"
    "on_actionToken_Table_triggered\0"
    "on_actionSymbol_Table_triggered\0"
    "on_actionQuaternary_File_triggered\0"
    "on_actionASM_File_triggered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      74,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  384,    2, 0x08 /* Private */,
       3,    1,  385,    2, 0x08 /* Private */,
       5,    0,  388,    2, 0x08 /* Private */,
       6,    2,  389,    2, 0x08 /* Private */,
       9,    0,  394,    2, 0x08 /* Private */,
      10,    0,  395,    2, 0x08 /* Private */,
      11,    1,  396,    2, 0x08 /* Private */,
      13,    1,  399,    2, 0x08 /* Private */,
      15,    1,  402,    2, 0x08 /* Private */,
      17,    2,  405,    2, 0x08 /* Private */,
      20,    2,  410,    2, 0x08 /* Private */,
      22,    2,  415,    2, 0x08 /* Private */,
      23,    2,  420,    2, 0x08 /* Private */,
      24,    1,  425,    2, 0x08 /* Private */,
      25,    0,  428,    2, 0x08 /* Private */,
      26,    0,  429,    2, 0x08 /* Private */,
      27,    0,  430,    2, 0x08 /* Private */,
      28,    0,  431,    2, 0x08 /* Private */,
      29,    0,  432,    2, 0x08 /* Private */,
      30,    0,  433,    2, 0x08 /* Private */,
      31,    0,  434,    2, 0x08 /* Private */,
      32,    0,  435,    2, 0x08 /* Private */,
      33,    0,  436,    2, 0x08 /* Private */,
      34,    0,  437,    2, 0x08 /* Private */,
      35,    0,  438,    2, 0x08 /* Private */,
      36,    0,  439,    2, 0x08 /* Private */,
      37,    0,  440,    2, 0x08 /* Private */,
      38,    1,  441,    2, 0x08 /* Private */,
      40,    1,  444,    2, 0x08 /* Private */,
      41,    1,  447,    2, 0x08 /* Private */,
      42,    0,  450,    2, 0x08 /* Private */,
      43,    0,  451,    2, 0x08 /* Private */,
      44,    0,  452,    2, 0x08 /* Private */,
      45,    0,  453,    2, 0x08 /* Private */,
      46,    0,  454,    2, 0x08 /* Private */,
      47,    0,  455,    2, 0x08 /* Private */,
      48,    0,  456,    2, 0x08 /* Private */,
      49,    0,  457,    2, 0x08 /* Private */,
      50,    0,  458,    2, 0x08 /* Private */,
      51,    0,  459,    2, 0x08 /* Private */,
      52,    0,  460,    2, 0x08 /* Private */,
      53,    0,  461,    2, 0x08 /* Private */,
      54,    0,  462,    2, 0x08 /* Private */,
      55,    0,  463,    2, 0x08 /* Private */,
      56,    0,  464,    2, 0x08 /* Private */,
      57,    0,  465,    2, 0x08 /* Private */,
      58,    0,  466,    2, 0x08 /* Private */,
      59,    0,  467,    2, 0x08 /* Private */,
      60,    0,  468,    2, 0x08 /* Private */,
      61,    0,  469,    2, 0x08 /* Private */,
      62,    0,  470,    2, 0x08 /* Private */,
      63,    0,  471,    2, 0x08 /* Private */,
      64,    1,  472,    2, 0x08 /* Private */,
      66,    0,  475,    2, 0x08 /* Private */,
      67,    0,  476,    2, 0x08 /* Private */,
      68,    0,  477,    2, 0x08 /* Private */,
      69,    0,  478,    2, 0x08 /* Private */,
      70,    0,  479,    2, 0x08 /* Private */,
      71,    0,  480,    2, 0x08 /* Private */,
      72,    0,  481,    2, 0x08 /* Private */,
      73,    0,  482,    2, 0x08 /* Private */,
      74,    0,  483,    2, 0x08 /* Private */,
      75,    0,  484,    2, 0x08 /* Private */,
      76,    0,  485,    2, 0x08 /* Private */,
      77,    0,  486,    2, 0x08 /* Private */,
      78,    0,  487,    2, 0x08 /* Private */,
      79,    0,  488,    2, 0x08 /* Private */,
      80,    0,  489,    2, 0x08 /* Private */,
      81,    0,  490,    2, 0x08 /* Private */,
      82,    0,  491,    2, 0x08 /* Private */,
      83,    0,  492,    2, 0x08 /* Private */,
      84,    0,  493,    2, 0x08 /* Private */,
      85,    0,  494,    2, 0x08 /* Private */,
      86,    0,  495,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    7,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   18,   19,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   21,   18,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   19,   21,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   19,   21,
    QMetaType::QString, QMetaType::QString,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   39,
    QMetaType::Void, QMetaType::Int,   39,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   65,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->save(); break;
        case 1: _t->open((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->newTab(); break;
        case 3: _t->selectText((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->highlightCurrentLine(); break;
        case 5: _t->updateHighlighterTheme(); break;
        case 6: _t->setTabWidth((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->updateLineNums((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->scrollOverview((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->setMainWindowStyle((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 10: _t->setTabWidgetStyle((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 11: _t->setLineNumStyle((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 12: _t->setOverViewStyle((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 13: { QString _r = _t->getFileType((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 14: _t->on_actionOpen_triggered(); break;
        case 15: _t->on_actionNew_triggered(); break;
        case 16: _t->on_actionSave_triggered(); break;
        case 17: _t->on_actionUndo_triggered(); break;
        case 18: _t->on_actionRedo_triggered(); break;
        case 19: _t->on_actionExit_triggered(); break;
        case 20: _t->on_actionSave_as_triggered(); break;
        case 21: _t->on_actionFind_triggered(); break;
        case 22: _t->on_actionHex_triggered(); break;
        case 23: _t->on_actionAscii_triggered(); break;
        case 24: _t->on_actionStrings_triggered(); break;
        case 25: _t->on_findLineEdit_returnPressed(); break;
        case 26: _t->on_actionAbout_triggered(); break;
        case 27: _t->on_tabWidget_tabCloseRequested((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 28: _t->on_tabWidget_currentChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 29: _t->onBlockCountChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 30: _t->onTextChanged(); break;
        case 31: _t->on_actionFullScreen_triggered(); break;
        case 32: _t->on_actionGoTo_triggered(); break;
        case 33: _t->on_actionAsm_triggered(); break;
        case 34: _t->on_actionC_triggered(); break;
        case 35: _t->on_actionCpluspluss_triggered(); break;
        case 36: _t->on_actionHtml_triggered(); break;
        case 37: _t->on_actionJava_triggered(); break;
        case 38: { bool _r = _t->confirmApplyTemplate();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 39: _t->on_actionCss_triggered(); break;
        case 40: _t->on_findButton_clicked(); break;
        case 41: _t->on_findPrevButton_clicked(); break;
        case 42: _t->on_actionFind_Next_triggered(); break;
        case 43: _t->findNext(); break;
        case 44: _t->findPrev(); break;
        case 45: _t->on_actionFind_Previous_triggered(); break;
        case 46: _t->on_actionReplace_triggered(); break;
        case 47: _t->on_replaceButton_clicked(); break;
        case 48: _t->on_actionDelete_line_triggered(); break;
        case 49: _t->on_actionRemove_word_triggered(); break;
        case 50: _t->on_replaceAllButton_clicked(); break;
        case 51: _t->on_replaceLineEdit_returnPressed(); break;
        case 52: _t->on_findLineEdit_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 53: _t->on_actionToggle_comment_triggered(); break;
        case 54: _t->on_actionOverview_triggered(); break;
        case 55: _t->on_actionDark_triggered(); break;
        case 56: _t->on_actionSolarized_Dark_triggered(); break;
        case 57: _t->on_actionJoin_Lines_triggered(); break;
        case 58: _t->on_actionMove_Line_Up_triggered(); break;
        case 59: _t->on_actionSwap_line_down_triggered(); break;
        case 60: _t->on_actionMenubar_triggered(); break;
        case 61: _t->on_actionSolarized_triggered(); break;
        case 62: _t->on_action8_triggered(); break;
        case 63: _t->on_action4_triggered(); break;
        case 64: _t->on_action2_triggered(); break;
        case 65: _t->on_actionClose_All_triggered(); break;
        case 66: _t->on_actionTommorrow_triggered(); break;
        case 67: _t->on_actionTommorrow_Night_triggered(); break;
        case 68: _t->on_actionRunIn16Bit_triggered(); break;
        case 69: _t->on_actionRunIn64Bit_triggered(); break;
        case 70: _t->on_actionToken_Table_triggered(); break;
        case 71: _t->on_actionSymbol_Table_triggered(); break;
        case 72: _t->on_actionQuaternary_File_triggered(); break;
        case 73: _t->on_actionASM_File_triggered(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 74)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 74;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 74)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 74;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
