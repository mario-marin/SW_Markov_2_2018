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
//float gffg[8][12];


//funcion que crea la matriz de transicion con las pij respectivas de CMPD
void llena_matriz_pij(vector <vector<float>> &vector1){
    vector< vector<float> >::iterator y;
    vector<float>::iterator x;
    for (y = vector1.begin(); y != vector1.end(); y++) {
        float sum = 0;
        for (x = y->begin(); x != y->end(); x++) {
            //*x=1;
            float random = lcgrand(50);
            sum=sum+random;
            *x=random;
            }
        for (x = y->begin(); x != y->end(); x++){
            *x=*x/sum;
        }
    }

}

//funcion crea la matriz de lambdas, cualquieras
void llena_matriz_lambdas(vector <vector<float>> &vector1, int n_e){
    for (int ii=0;ii<n_e;++ii){
        for(int jj=0;jj<n_e;++jj){
            if(ii==jj){
                vector1[ii][jj]=0;
            }
            else{
                float random=lcgrand(50)*100;
                vector1[ii][jj]=random;
            }
        }
    }


}

void matriz_delta_t(vector <vector<float>> &vector1, float delta_t, int n_e){
    float aux;
    for (int ii=0;ii<n_e;++ii){
        aux=0;
        for(int jj=0;jj<n_e;++jj){
                   vector1[ii][jj]=vector1[ii][jj]*delta_t;
                   aux=aux+vector1[ii][jj];
        }
        vector1[ii][ii]=1-aux;
    }
}

void imprime_vector_doble(vector <vector<float>> &vector1){
    vector< vector<float> >::iterator fila;
    vector<float>::iterator col;
    for (fila = vector1.begin(); fila != vector1.end(); fila++) {
        for (col = fila->begin(); col != fila->end(); col++) {
            cout<<*col<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
    return;
}

float prob_ij(vector <vector<float>> &vector1, int n_e, int n, int i, int e_i, float (&arr)[8][12]){
    float aux = 0;
    if(n==0 && i==e_i){
        return 1;
    }
    else if (n==0 && i!=e_i){
        return 0;
    }
    else{
        for(int jj = 0; jj<n_e;++jj){
            aux = aux + prob_ij(vector1, n_e, n-1, jj, e_i, arr)*(vector1[jj][i]);
            //cout<<aux<<" j: "<<jj<<" n: "<<n<<endl;
        }


               // cout<<"n: "<<n<<" i: "<<i<<" prob, aux: "<<aux<<endl;

}

        arr[i][n]=aux;
        return aux;
    }


/*float prob_ij2(vector <vector<float>> &vector1, int n_e, int n, int i, int e_i, float (&arr)[8][12]){
    float aux = 0;
    if(n==0 && i==e_i){
        return 1;
    }
    else if (n==0 && i!=e_i){
        return 0;
    }
    else if(n!=1){
        for(int jj = 0; jj<n_e;++jj){
            aux = aux + prob_ij(vector1, n_e, n-1, jj, e_i)*(vector1[jj][i]);
        }
    }
        else{
            aux=(n_e+1)*prob_ij(vector1, n_e, n-1, i, e_i)*(vector1[0][i]);
        }
    arr[i][n] = aux;
    cout<<"n: "<<n<<" i: "<<i<<" prob, aux: "<<aux<<endl;
    return aux;
    }
*/

void test_edit(float (&arr)[8][12]){
    //cout<<endl;
    for (int i=0;i<8;++i){
        for(int j=0;j<12;j++){
            if(arr[i][j]<0.0001 || arr[i][j]>1)
            arr[i][j]=0;
        }

    //cout<<endl;
    }

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


int main(int argc, char **argv)
{





    int numero_estados = 4;
    int n = 12;
    int target = 2;
    int estado_inicial = 0;
    float deltat = 0.001;
    //x estados, pero la matriz se inicia del 0 al x-1
    vector< vector<float> >matriz_transicion(numero_estados, vector<float>(numero_estados));
    vector< vector<float> >matriz_lambdas(numero_estados, vector<float>(numero_estados));

    vector< vector<float> >matriz_transicion_manual{{0.1,0.4,0.1,0.4},{0.1,0.3,0.5,0.1},{0.3,0.1,0.4,0.2},{0.4,0.3,0.1,0.2}};


    llena_matriz_pij(matriz_transicion);
    imprime_vector_doble(matriz_transicion);
    imprime_vector_doble(matriz_transicion_manual);

    float arrf[8][12];




    //float prob1 = prob_ij(matriz_transicion,numero_estados,n,target,estado_inicial, arrf);
    float prob11=prob_ij(matriz_transicion_manual,numero_estados,n,target,estado_inicial, arrf);

    test_edit(arrf);
    imprime_arr(arrf);

    //float prob2 = prob_ij2(matriz_transicion,numero_estados,n,target,estado_inicial, arrf);
    //cout<<"fc1: "<<prob1<<" "<<endl;
    //cout<<"fc2: "<<prob2<<endl;
    //f2; prob_ij2 es mas rapida ssi n>>>numero de estados, sino es mas lenta o lo mismo

    //imprime_arr(arrf);

    //test(matriz_transicion,numero_estados);

    //llena_matriz_lambdas(matriz_lambdas,numero_estados);
    //imprime_vector_doble(matriz_lambdas);
    //cout<<endl;
    //matriz_delta_t(matriz_lambdas,deltat,numero_estados);
    //imprime_vector_doble(matriz_lambdas);










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

    GraphModifier *modifier = new GraphModifier(widgetgraph, arrf);

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
