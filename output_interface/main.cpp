#include "graphmodifier.h"
#include <iostream>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QSlider>
#include <QtWidgets/QFontComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMessageBox>
#include <QtGui/QScreen>
#include <QtGui/QFontDatabase>
#include "lcgrand.c"

using namespace std;
using namespace QtDataVisualization;



void imprime_arr(float (&arr)[8][12]);
//Funcion para imprimir un arreglo de 8 filas con 12 col

void vec_to_arr(vector<vector<float> > &vec, float (&arr)[8][12]);
//Funcion para copiar los datos de un vector [8][12] a un arreglo de [8][12]

int main(int argc, char **argv)
{

    float arrf[8][12]={{0}}; //inicializacion de un vector de [8][1] con 0s

    std::vector<std::vector<float>> aux_vec(8, std::vector<float>(12, 0));

    //llenado manual de el vector 2D con valores reales, (resultados de mm)
    aux_vec[0]={1, 0, 0.5, 0.25, 0.33, 0.2945, 0.29875, 0.29523, 0.29362, 0.293142, 0.292406, 0.292196};
    aux_vec[1]={0, 0.5, 0.25, 0.33, 0.2945 ,0.29875, 0.29523, 0.29362, 0.293142, 0.292406, 0.292196, 0.291961};
    aux_vec[2]={0, 0, 0.15, 0.135, 0.18, 0.18465, 0.195885, 0.20016, 0.203409, 0.205335, 0.20647, 0.207207};
    aux_vec[3]={0, 0.5, 0.1, 0.285, 0.1955, 0.2221, 0.210135, 0.210991, 0.209829, 0.209116, 0.208928, 0.208636};
    aux_vec[4]={0,0,0,0,0,0,0,0,0,0,0,0};
    aux_vec[5]={0,0,0,0,0,0,0,0,0,0,0,0};
    aux_vec[6]={0,0,0,0,0,0,0,0,0,0,0,0};
    aux_vec[7]={0,0,0,0,0,0,0,0,0,0,0,0};

    //vec_to_arr(aux_vec,(float *)arrf);
    vec_to_arr(aux_vec, arrf);
    imprime_arr(arrf);





    QApplication app(argc, argv);
    Q3DBars *widgetgraph = new Q3DBars();
    QWidget *container = QWidget::createWindowContainer(widgetgraph);

    if (!widgetgraph->hasContext()) {
        QMessageBox msgBox;
        msgBox.setText("Couldn't initialize the OpenGL context.");
        msgBox.exec();
        return -1;
    }

    QSize screenSize = widgetgraph->screen()->size();
    container->setMinimumSize(QSize(screenSize.width() / 2, screenSize.height() / 1.5));
    container->setMaximumSize(screenSize);
    container->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    container->setFocusPolicy(Qt::StrongFocus);

    QWidget *widget = new QWidget;
    QHBoxLayout *hLayout = new QHBoxLayout(widget);
    QVBoxLayout *vLayout = new QVBoxLayout();
    hLayout->addWidget(container, 1);
    hLayout->addLayout(vLayout);

    widget->setWindowTitle(QStringLiteral("Ocupa data 2"));

    QComboBox *themeList = new QComboBox(widget);
    themeList->addItem(QStringLiteral("Qt"));
    themeList->addItem(QStringLiteral("Primary Colors"));
    themeList->addItem(QStringLiteral("Digia"));
    themeList->addItem(QStringLiteral("Stone Moss"));
    themeList->addItem(QStringLiteral("Army Blue"));
    themeList->addItem(QStringLiteral("Retro"));
    themeList->addItem(QStringLiteral("Ebony"));
    themeList->addItem(QStringLiteral("Isabelle"));
    themeList->setCurrentIndex(0);

    QPushButton *labelButton = new QPushButton(widget);
    labelButton->setText(QStringLiteral("Change label style"));

    QCheckBox *smoothCheckBox = new QCheckBox(widget);
    smoothCheckBox->setText(QStringLiteral("Smooth bars"));
    smoothCheckBox->setChecked(false);

    QComboBox *barStyleList = new QComboBox(widget);
    barStyleList->addItem(QStringLiteral("Bar"), int(QAbstract3DSeries::MeshBar));
    barStyleList->addItem(QStringLiteral("Pyramid"), int(QAbstract3DSeries::MeshPyramid));
    barStyleList->addItem(QStringLiteral("Cone"), int(QAbstract3DSeries::MeshCone));
    barStyleList->addItem(QStringLiteral("Cylinder"), int(QAbstract3DSeries::MeshCylinder));
    barStyleList->addItem(QStringLiteral("Bevel bar"), int(QAbstract3DSeries::MeshBevelBar));
    barStyleList->addItem(QStringLiteral("Sphere"), int(QAbstract3DSeries::MeshSphere));
    barStyleList->setCurrentIndex(4);

    QPushButton *cameraButton = new QPushButton(widget);
    cameraButton->setText(QStringLiteral("Change camera preset"));

    QPushButton *zoomToSelectedButton = new QPushButton(widget);
    zoomToSelectedButton->setText(QStringLiteral("Zoom to selected bar"));

    QComboBox *selectionModeList = new QComboBox(widget);
    selectionModeList->addItem(QStringLiteral("None"),
                               int(QAbstract3DGraph::SelectionNone));
    selectionModeList->addItem(QStringLiteral("Bar"),
                               int(QAbstract3DGraph::SelectionItem));
    selectionModeList->addItem(QStringLiteral("Row"),
                               int(QAbstract3DGraph::SelectionRow));
    selectionModeList->addItem(QStringLiteral("Bar and Row"),
                               int(QAbstract3DGraph::SelectionItemAndRow));
    selectionModeList->addItem(QStringLiteral("Column"),
                               int(QAbstract3DGraph::SelectionColumn));
    selectionModeList->addItem(QStringLiteral("Bar and Column"),
                               int(QAbstract3DGraph::SelectionItemAndColumn));
    selectionModeList->addItem(QStringLiteral("Row and Column"),
                               int(QAbstract3DGraph::SelectionRowAndColumn));
    selectionModeList->addItem(QStringLiteral("Bar, Row and Column"),
                               int(QAbstract3DGraph::SelectionItemRowAndColumn));
    selectionModeList->addItem(QStringLiteral("Slice into Row"),
                               int(QAbstract3DGraph::SelectionSlice | QAbstract3DGraph::SelectionRow));
    selectionModeList->addItem(QStringLiteral("Slice into Row and Item"),
                               int(QAbstract3DGraph::SelectionSlice | QAbstract3DGraph::SelectionItemAndRow));
    selectionModeList->addItem(QStringLiteral("Slice into Column"),
                               int(QAbstract3DGraph::SelectionSlice | QAbstract3DGraph::SelectionColumn));
    selectionModeList->addItem(QStringLiteral("Slice into Column and Item"),
                               int(QAbstract3DGraph::SelectionSlice | QAbstract3DGraph::SelectionItemAndColumn));
    selectionModeList->addItem(QStringLiteral("Multi: Bar, Row, Col"),
                               int(QAbstract3DGraph::SelectionItemRowAndColumn
                                   | QAbstract3DGraph::SelectionMultiSeries));
    selectionModeList->addItem(QStringLiteral("Multi, Slice: Row, Item"),
                               int(QAbstract3DGraph::SelectionSlice | QAbstract3DGraph::SelectionItemAndRow
                                   | QAbstract3DGraph::SelectionMultiSeries));
    selectionModeList->addItem(QStringLiteral("Multi, Slice: Col, Item"),
                               int(QAbstract3DGraph::SelectionSlice | QAbstract3DGraph::SelectionItemAndColumn
                                   | QAbstract3DGraph::SelectionMultiSeries));
    selectionModeList->setCurrentIndex(1);

    QCheckBox *backgroundCheckBox = new QCheckBox(widget);
    backgroundCheckBox->setText(QStringLiteral("Show background"));
    backgroundCheckBox->setChecked(false);

    QCheckBox *gridCheckBox = new QCheckBox(widget);
    gridCheckBox->setText(QStringLiteral("Show grid"));
    gridCheckBox->setChecked(true);

    QCheckBox *seriesCheckBox = new QCheckBox(widget);
    seriesCheckBox->setText(QStringLiteral("Show second series"));
    seriesCheckBox->setChecked(false);

    QCheckBox *reverseValueAxisCheckBox = new QCheckBox(widget);
    reverseValueAxisCheckBox->setText(QStringLiteral("Reverse value axis"));
    reverseValueAxisCheckBox->setChecked(false);

    QCheckBox *reflectionCheckBox = new QCheckBox(widget);
    reflectionCheckBox->setText(QStringLiteral("Show reflections"));
    reflectionCheckBox->setChecked(false);

    QSlider *rotationSliderX = new QSlider(Qt::Horizontal, widget);
    rotationSliderX->setTickInterval(30);
    rotationSliderX->setTickPosition(QSlider::TicksBelow);
    rotationSliderX->setMinimum(-180);
    rotationSliderX->setValue(0);
    rotationSliderX->setMaximum(180);
    QSlider *rotationSliderY = new QSlider(Qt::Horizontal, widget);
    rotationSliderY->setTickInterval(15);
    rotationSliderY->setTickPosition(QSlider::TicksAbove);
    rotationSliderY->setMinimum(-90);
    rotationSliderY->setValue(0);
    rotationSliderY->setMaximum(90);

    QSlider *fontSizeSlider = new QSlider(Qt::Horizontal, widget);
    fontSizeSlider->setTickInterval(10);
    fontSizeSlider->setTickPosition(QSlider::TicksBelow);
    fontSizeSlider->setMinimum(1);
    fontSizeSlider->setValue(30);
    fontSizeSlider->setMaximum(100);

    QFontComboBox *fontList = new QFontComboBox(widget);
    fontList->setCurrentFont(QFont("Times New Roman"));

    QComboBox *shadowQuality = new QComboBox(widget);
    shadowQuality->addItem(QStringLiteral("None"));
    shadowQuality->addItem(QStringLiteral("Low"));
    shadowQuality->addItem(QStringLiteral("Medium"));
    shadowQuality->addItem(QStringLiteral("High"));
    shadowQuality->addItem(QStringLiteral("Low Soft"));
    shadowQuality->addItem(QStringLiteral("Medium Soft"));
    shadowQuality->addItem(QStringLiteral("High Soft"));
    shadowQuality->setCurrentIndex(5);

    QComboBox *rangeList = new QComboBox(widget);
    rangeList->addItem(QStringLiteral("0"));
    rangeList->addItem(QStringLiteral("1"));
    rangeList->addItem(QStringLiteral("2"));
    rangeList->addItem(QStringLiteral("3"));
    rangeList->addItem(QStringLiteral("3"));
    rangeList->addItem(QStringLiteral("4"));
    rangeList->addItem(QStringLiteral("5"));
    rangeList->addItem(QStringLiteral("6"));
    rangeList->addItem(QStringLiteral("All"));
    rangeList->setCurrentIndex(8);

    QCheckBox *axisTitlesVisibleCB = new QCheckBox(widget);
    axisTitlesVisibleCB->setText(QStringLiteral("Axis titles visible"));
    axisTitlesVisibleCB->setChecked(true);

    QCheckBox *axisTitlesFixedCB = new QCheckBox(widget);
    axisTitlesFixedCB->setText(QStringLiteral("Axis titles fixed"));
    axisTitlesFixedCB->setChecked(true);

    QSlider *axisLabelRotationSlider = new QSlider(Qt::Horizontal, widget);
    axisLabelRotationSlider->setTickInterval(10);
    axisLabelRotationSlider->setTickPosition(QSlider::TicksBelow);
    axisLabelRotationSlider->setMinimum(0);
    axisLabelRotationSlider->setValue(30);
    axisLabelRotationSlider->setMaximum(90);

    vLayout->addWidget(new QLabel(QStringLiteral("Rotate horizontally")));
    vLayout->addWidget(rotationSliderX, 0, Qt::AlignTop);
    vLayout->addWidget(new QLabel(QStringLiteral("Rotate vertically")));
    vLayout->addWidget(rotationSliderY, 0, Qt::AlignTop);
    vLayout->addWidget(labelButton, 0, Qt::AlignTop);
    vLayout->addWidget(cameraButton, 0, Qt::AlignTop);
    vLayout->addWidget(zoomToSelectedButton, 0, Qt::AlignTop);
    vLayout->addWidget(backgroundCheckBox);
    vLayout->addWidget(gridCheckBox);
    vLayout->addWidget(smoothCheckBox);
    vLayout->addWidget(reflectionCheckBox);
    vLayout->addWidget(seriesCheckBox);
    vLayout->addWidget(reverseValueAxisCheckBox);
    vLayout->addWidget(axisTitlesVisibleCB);
    vLayout->addWidget(axisTitlesFixedCB);
    //vLayout->addWidget(new QLabel(QStringLiteral("Show year")));
    //vLayout->addWidget(rangeList);
    vLayout->addWidget(new QLabel(QStringLiteral("Change bar style")));
    vLayout->addWidget(barStyleList);
    vLayout->addWidget(new QLabel(QStringLiteral("Change selection mode")));
    vLayout->addWidget(selectionModeList);
    vLayout->addWidget(new QLabel(QStringLiteral("Change theme")));
    vLayout->addWidget(themeList);
    vLayout->addWidget(new QLabel(QStringLiteral("Adjust shadow quality")));
    vLayout->addWidget(shadowQuality);
    vLayout->addWidget(new QLabel(QStringLiteral("Change font")));
    vLayout->addWidget(fontList);
    vLayout->addWidget(new QLabel(QStringLiteral("Adjust font size")));
    vLayout->addWidget(fontSizeSlider);
    vLayout->addWidget(new QLabel(QStringLiteral("Axis label rotation")));
    vLayout->addWidget(axisLabelRotationSlider, 1, Qt::AlignTop);

    GraphModifier *modifier = new GraphModifier(widgetgraph, arrf);  //constructor que recibe el arreglo de datos

    QObject::connect(rotationSliderX, &QSlider::valueChanged, modifier, &GraphModifier::rotateX);
    QObject::connect(rotationSliderY, &QSlider::valueChanged, modifier, &GraphModifier::rotateY);

    QObject::connect(labelButton, &QPushButton::clicked, modifier,
                     &GraphModifier::changeLabelBackground);
    QObject::connect(cameraButton, &QPushButton::clicked, modifier,
                     &GraphModifier::changePresetCamera);
    QObject::connect(zoomToSelectedButton, &QPushButton::clicked, modifier,
                     &GraphModifier::zoomToSelectedBar);

    QObject::connect(backgroundCheckBox, &QCheckBox::stateChanged, modifier,
                     &GraphModifier::setBackgroundEnabled);
    QObject::connect(gridCheckBox, &QCheckBox::stateChanged, modifier,
                     &GraphModifier::setGridEnabled);
    QObject::connect(smoothCheckBox, &QCheckBox::stateChanged, modifier,
                     &GraphModifier::setSmoothBars);
    QObject::connect(seriesCheckBox, &QCheckBox::stateChanged, modifier,
                     &GraphModifier::setSeriesVisibility);
    QObject::connect(reverseValueAxisCheckBox, &QCheckBox::stateChanged, modifier,
                     &GraphModifier::setReverseValueAxis);
    QObject::connect(reflectionCheckBox, &QCheckBox::stateChanged, modifier,
                     &GraphModifier::setReflection);

    QObject::connect(modifier, &GraphModifier::backgroundEnabledChanged,
                     backgroundCheckBox, &QCheckBox::setChecked);
    QObject::connect(modifier, &GraphModifier::gridEnabledChanged,
                     gridCheckBox, &QCheckBox::setChecked);

    QObject::connect(rangeList, SIGNAL(currentIndexChanged(int)), modifier,
                     SLOT(changeRange(int)));

    QObject::connect(barStyleList, SIGNAL(currentIndexChanged(int)), modifier,
                     SLOT(changeStyle(int)));

    QObject::connect(selectionModeList, SIGNAL(currentIndexChanged(int)), modifier,
                     SLOT(changeSelectionMode(int)));

    QObject::connect(themeList, SIGNAL(currentIndexChanged(int)), modifier,
                     SLOT(changeTheme(int)));

    QObject::connect(shadowQuality, SIGNAL(currentIndexChanged(int)), modifier,
                     SLOT(changeShadowQuality(int)));

    QObject::connect(modifier, &GraphModifier::shadowQualityChanged, shadowQuality,
                     &QComboBox::setCurrentIndex);
    QObject::connect(widgetgraph, &Q3DBars::shadowQualityChanged, modifier,
                     &GraphModifier::shadowQualityUpdatedByVisual);

    QObject::connect(fontSizeSlider, &QSlider::valueChanged, modifier,
                     &GraphModifier::changeFontSize);
    QObject::connect(fontList, &QFontComboBox::currentFontChanged, modifier,
                     &GraphModifier::changeFont);

    QObject::connect(modifier, &GraphModifier::fontSizeChanged, fontSizeSlider,
                     &QSlider::setValue);
    QObject::connect(modifier, &GraphModifier::fontChanged, fontList,
                     &QFontComboBox::setCurrentFont);

    QObject::connect(axisTitlesVisibleCB, &QCheckBox::stateChanged, modifier,
                     &GraphModifier::setAxisTitleVisibility);
    QObject::connect(axisTitlesFixedCB, &QCheckBox::stateChanged, modifier,
                     &GraphModifier::setAxisTitleFixed);
    QObject::connect(axisLabelRotationSlider, &QSlider::valueChanged, modifier,
                     &GraphModifier::changeLabelRotation);
    widget->show();
    return app.exec();
}


void imprime_arr(float (&arr)[8][12]){
    cout<<endl;
    for (int i=0;i<8;++i){
        for(int j=0;j<12;j++){
            cout<<arr[i][j]<<" ";
        }
    cout<<endl;
    }

}

void vec_to_arr(vector<vector<float> > &vec, float (&arr)[8][12]){

    for (int i=0;i<8;++i){
        for(int j=0;j<12;j++){
            arr[i][j]=vec[i][j];
        }

    }

}
