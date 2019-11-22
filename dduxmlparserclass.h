#ifndef DDUXMLPARSERCLASS_H
#define DDUXMLPARSERCLASS_H
/*#include <QWidget>
#include<iostream>
#include<list>
#include<QString>
#include<QDebug>
#include<QStringList>*/
#include "dduwaypointclass.h"
#include "ddulocationclass.h"
#include "ddurouteclass.h"
#include "dduxmltagnameclass.h"
#include "QProgressBar"
//#include "ddudownloaduploadscreenclass.h"
#include "ddutalinhandlerclass.h"
#include "Global.h"

#include "xercesc/dom/DOMImplementation.hpp"
#include "xercesc/parsers/XercesDOMParser.hpp"
#include<xercesc/parsers/XercesDOMParser.hpp>
#include<xercesc/dom/DOMWriter.hpp>
#include<xercesc/dom/DOMDocument.hpp>
#include<xercesc/dom/DOMElement.hpp>
#include<xercesc/dom/DOMText.hpp>
#include<xercesc/dom/DOMNodeList.hpp>
#include<xercesc/dom/DOMImplementationRegistry.hpp>
#include<xercesc/framework/LocalFileFormatTarget.hpp>
#define CONFIG_FILE_PATH "./BusinessLogic/Config.xml"
struct ConfigurationParameterStruct
{
    QString szDatabaseUserName;                 // A String variable to store the database user name
    QString szDatabasePassword;                 // A String variable to store the database password
    QString szDatabaseName;                     // A String variable to store the database name
    enum CoOrdinateRefSys eReferenceSystem;   // A enum variable of type cordinate reference system to store the type of reference system to be used
    QString szMapDatum;                         // A String variable to store the map datum value read from the configuration file
    QString szMapDatumForTalin;                 // A String variable to store the map datum value to be send to talin
    char cMapDatumForTalin[6];
    QString szHeading;                          // A String variable to store the heading
    QString szParameterPassword;                // A String variable to store the parameter updation password
};

GLOBAL struct ConfigurationParameterStruct gstConfParam;        // A global structure variable to store the configuration parameters read from the configuration file
class DduXmlParserClass
{
//    Q_OBJECT
private:
    xercesc_2_7 :: DOMImplementation*   mptrobj_domImplementation;  // Dom Implementation pointer used to store the implementation object given by the registry
    xercesc_2_7 :: XercesDOMParser*     mptrobj_domParser;          // Dom parser pointer to store the object of parser
    xercesc_2_7 :: DOMWriter*           mptrobj_theSerializer;      // To store the writer obejct
    xercesc_2_7 :: XMLFormatTarget*     mptrobj_myFormTarget;       // To store the form target
    xercesc_2_7 :: DOMDocument*         mptrobj_domDocument;        // To store the document object
    xercesc_2_7 :: DOMElement*          mptrobj_rootElement;        // To store the object of root element of the file
    xercesc_2_7 :: DOMText*             mptrobj_textNode;           // To store the object of text node
    int count;                                                      // To store the count
public:
    DduXmlParserClass();
    ~DduXmlParserClass();

    int ReadConfigurationXML();
    //void ReadConfigurationXML1(QString &D,QString &RS);
//    void ReadConfigurationXML1(QString &DbUser,QString &DbName,QString &DbPassword);
    int WriteConfigurationFile(QString);
    //void WriteConfigurationFile1(QString ,QString );
    int ReadRouteXML(list<DduRouteClass>*,char*);
    int ReadWaypointXML(list<DduWaypointClass>*,char*);
    int WriteRouteXML(list<DduRouteClass>*,char*);
    int WriteWaypointXML(list<DduWaypointClass>*,char*);
    int DemoOne();
    void Progress();

};

using namespace std;
using namespace xercesc_2_7;
#endif // DDUXMLPARSERCLASS_H


