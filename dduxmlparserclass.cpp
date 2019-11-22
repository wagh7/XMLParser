#include "dduxmlparserclass.h"
#include "QLocale"
#include "QDebug"

DduXmlParserClass::DduXmlParserClass()
{
    this->count=gconstValueZero;
    try
    {
        //Parser initialization
        xercesc_2_7:: XMLPlatformUtils::Initialize();
        mptrobj_domParser= new xercesc_2_7 ::XercesDOMParser();
        //#ifdef DEBUG_XML
        //	qDebug()<<__FILE__ << "::"<< __FUNCTION__<<" :: "<<__LINE__ << "parser initialize"<<parser<<endl;
        //#endif
        // Set the scanner to scan the xml documents.
        mptrobj_domParser -> useScanner(xercesc_2_7 :: XMLUni::fgWFXMLScanner);
    }
    catch(xercesc_2_7::XMLException& ex)
    {
        char* ptrcErrorMessage = xercesc_2_7::XMLString::transcode(ex.getMessage());        // A character pointer to store the error message
#ifdef DEBUG_FLAG
        qDebug() << __FILE__ << "::" << __FUNCTION__ << "::" << __LINE__ << endl;
        qDebug() << ptrcErrorMessage << endl;
#endif
        xercesc_2_7::XMLString::release(&ptrcErrorMessage);
        exit(EXIT_FAILURE);
    }

    //connect(this,SIGNAL(demo1(int)),obj,SLOT(test()));
}

DduXmlParserClass::~DduXmlParserClass()
{
    //delete impl;
    //delete parser;
    //delete parser1;
    //delete theSerializer;
    //delete myFormTarget;
    //delete doc;
    //delete root;
    //delete textNode;
    delete mptrobj_domParser;
    xercesc_2_7 :: XMLPlatformUtils::Terminate();
}


/*

  This function reads  the Configuration file and set the values read from it to the global structure
  which will then be used for performing other functionality

  @return 1 if successsfully read and 0 if any exception occurs
 */
int DduXmlParserClass::ReadConfigurationXML()
{
#ifdef DEBUG_FLAG
    qDebug()<<"Read Configuration file called";
#endif
    const char *ptrcFileName=CONFIG_FILE_PATH;  // A chracter pointer to store the file path
    const XMLCh* ptrobjCurrentText;             // A temporary xmlchar pointer to store the the current text while parsing the document
    DduXmlConfigurationTagNameClass objTagName;    // A temporary object of Configuration tag class having tagnames of configuration file
    XMLCh* ptrobjFilePointer;                   // A char pointer to store the file name
#ifdef DEBUG_FLAG
    qDebug() << "File Name is before parssing " << ptrcFileName<< endl;
    qDebug() << "Ptr value is before transcoding " << ptrobjFilePointer << endl;
#endif
    try{
        ptrobjFilePointer = xercesc_2_7::XMLString::transcode(ptrcFileName);
#ifdef DEBUG_FLAG
        qDebug() << "Ptr value is after transcoding " << ptrobjFilePointer << endl;
#endif
        mptrobj_domParser->parse(ptrobjFilePointer);
#ifdef DEBUG_FLAG
        qDebug()<<"Parsing Successfull";
#endif
        if(mptrobj_domParser->getErrorCount() > gconstValueZero)
        {
#ifdef DEBUG_FLAG
            qDebug()<<ptrcFileName << " file format not valid, parsing unsuccessful" <<endl;
            qDebug()<< mptrobj_domParser->getErrorCount() << endl;
#endif
            return gconstValueZero;
        }
        DOMDocument *ptrobjXmlDoc=mptrobj_domParser->getDocument(); // A temporary document pointer to store the reference of the document object of the given file
        XMLString :: release(&ptrobjFilePointer);
        xercesc_2_7 :: DOMElement *ptrobjXmlRoot=ptrobjXmlDoc->getDocumentElement();    // A element pointer to store the root element
        xercesc_2_7 :: DOMNodeList* ptrobjDduConfigParam = ptrobjXmlRoot->getChildNodes();      // A node list pointer to store the all the child nodes of the root element
        const  XMLSize_t objNodeCount = ptrobjDduConfigParam->getLength();  // A size variable to store the no of child node under the root node ** in our case it will be one
        // For all nodes, children of "root" in the XML tree.
        for( XMLSize_t objSecondIndex = gconstValueZero; objSecondIndex < objNodeCount; ++objSecondIndex )
        {
            xercesc_2_7 :: DOMNode* ptrobjCurrentNode = ptrobjDduConfigParam->item(objSecondIndex);    // A temporary node element used to get every childNode object one by one
            if( ptrobjCurrentNode->getNodeType() &&  // true is not NULL
                ptrobjCurrentNode->getNodeType() == xercesc_2_7 ::DOMNode::ELEMENT_NODE ) // is element
            {
                xercesc_2_7 :: DOMElement* ptrobjCurrentElement=(xercesc_2_7::DOMElement*)ptrobjCurrentNode;    // A pointer to store the current element
                if( xercesc_2_7::XMLString::equals(ptrobjCurrentElement->getTagName(), objTagName.mptrobj_tagConfigurationDetails))
                {
#ifdef DEBUG_FLAG
                    qDebug() << __FILE__ << "::" << __FUNCTION__ << "::" << __LINE__ << " Configuration Details:: " << ptrobjCurrentElement->getTagName() <<endl;
#endif
                    xercesc_2_7 :: DOMNodeList* ptrobjChildrens = ptrobjCurrentElement->getChildNodes();   // Store the children of the child node of root that is sub children
                    const  XMLSize_t objChildCount = ptrobjChildrens->getLength();    //  Store the no of childrens
                    for(XMLSize_t objFirstIndex=gconstValueZero;objFirstIndex<objChildCount;objFirstIndex++)
                    {
                        xercesc_2_7 :: DOMNode* ptrobjCurrentNode = ptrobjChildrens->item(objFirstIndex);      // A temporary node element used to get every childNode object one by one
                        if( ptrobjCurrentNode->getNodeType() &&  // true is not NULL
                            ptrobjCurrentNode->getNodeType() == xercesc_2_7 ::DOMNode::ELEMENT_NODE ) // is element
                        {
                            xercesc_2_7 :: DOMElement* ptrobjCurrentElement=(xercesc_2_7::DOMElement*)ptrobjCurrentNode;        // A pointer to store the current element
                            if( xercesc_2_7::XMLString::equals(ptrobjCurrentElement->getTagName(), objTagName.mptrobj_tagDatabaseName))
                            {
                                ptrobjCurrentText=ptrobjCurrentElement->getTextContent();
                                gstConfParam.szDatabaseName=XMLString::transcode(ptrobjCurrentText);
#ifdef DEBUG_FLAG
                                qDebug()<<"Database Name  " << gstConfParam.szDatabaseName;
#endif

                            }
                            //DB_Password
                            else if(xercesc_2_7::XMLString::equals(ptrobjCurrentElement->getTagName(), objTagName.mptrobj_tagDatabasePassword))
                            {
                                ptrobjCurrentText=ptrobjCurrentElement->getTextContent();
                                gstConfParam.szDatabasePassword=XMLString::transcode(ptrobjCurrentText);
#ifdef DEBUG_FLAG
                                qDebug()<<"Database Password " << gstConfParam.szDatabasePassword;
#endif
                            }
                            //DB_User Name
                            else if(xercesc_2_7::XMLString::equals(ptrobjCurrentElement->getTagName(), objTagName.mptrobj_tagDatabaseUserName))
                            {
                                ptrobjCurrentText=ptrobjCurrentElement->getTextContent();
                                gstConfParam.szDatabaseUserName=XMLString::transcode(ptrobjCurrentText);
#ifdef DEBUG_FLAG
                                qDebug()<<"Database user name " << gstConfParam.szDatabaseUserName;
#endif
                            }
                            //Datum ID
                            else if(xercesc_2_7::XMLString::equals(ptrobjCurrentElement->getTagName(), objTagName.mptrobj_tagDatumId))
                            {
                                ptrobjCurrentText=ptrobjCurrentElement->getTextContent();
                                gstConfParam.szMapDatum=XMLString::transcode(ptrobjCurrentText);
                                gstConfParam.szMapDatumForTalin="WGD   ";
                                strncpy(gstConfParam.cMapDatumForTalin,"WGD   ",6);
                                // to be change (read from XML file )
#ifdef DEBUG_FLAG
                                qDebug()<<"Datum Id " << gstConfParam.szMapDatum;
#endif
                            }
                            //Reference system
                            else if(xercesc_2_7::XMLString::equals(ptrobjCurrentElement->getTagName(), objTagName.mptrobj_tagReferenceSystem))
                            {
                                ptrobjCurrentText=ptrobjCurrentElement->getTextContent();
                                QString szReferenceSystem=XMLString::transcode(ptrobjCurrentText);      // A temporary string variable to store the text read from xml file
                                if(szReferenceSystem.compare("UTM")==gconstValueZero)
                                {
                                    gstConfParam.eReferenceSystem=UTM;
                                }
                                else if(szReferenceSystem.compare("GEODETIC")==gconstValueZero)
                                {
                                    gstConfParam.eReferenceSystem=GEODETIC;
                                }
                                else if(szReferenceSystem.compare("MGRS")==gconstValueZero)
                                {
                                    gstConfParam.eReferenceSystem=MGRS;
                                }
                                else
                                {
                                    gstConfParam.eReferenceSystem=INVALID;
                                }
#ifdef DEBUG_FLAG
                                qDebug()<<"Reference System " <<gstConfParam.eReferenceSystem ;
#endif
                            }
                            //Parameter-Password
                            else if(xercesc_2_7::XMLString::equals(ptrobjCurrentElement->getTagName(), objTagName.mptrobj_tagParameterUpdationPassword))
                            {
                                ptrobjCurrentText=ptrobjCurrentElement->getTextContent();
                                gstConfParam.szParameterPassword=XMLString::transcode(ptrobjCurrentText);
#ifdef DEBUG_FLAG
                                qDebug()<<"update Parameter password#########" <<gstConfParam.szParameterPassword;
#endif
                            }
                            else if(xercesc_2_7::XMLString::equals(ptrobjCurrentElement->getTagName(), objTagName.mptrobj_tagHeading))
                            {
                                ptrobjCurrentText=ptrobjCurrentElement->getTextContent();
                                gstConfParam.szHeading=QString(XMLString::transcode(ptrobjCurrentText));
#ifdef DEBUG_FLAG
                                qDebug()<<"Heading :" <<gstConfParam.szHeading;
#endif
                            }
                            else
                            {
                                continue;
                            }
                        }
                    }
                }
            }
        }
        return gconstValueOne;
    }
    catch(XMLException& e)
    {
        char* ptrcErrorMessage = xercesc_2_7::XMLString::transcode(e.getMessage()); // A character pointer to store the error message
#ifdef DEBUG_FLAG
        qDebug() << __FILE__ << "::" << __FUNCTION__ << "::" << __LINE__ <<endl;
        qDebug() << ptrcErrorMessage <<endl;
#endif
        xercesc_2_7::XMLString::release( &ptrcErrorMessage );
        return gconstValueZero;
    }
    catch(...)
    {
#ifdef DEBUG_FLAG
        qDebug()<<"UNKNOWN XML EXCEPTION";
#endif
        return gconstValueZero;
    }
}

/*
  Used to update the parameter updation password

    This function first reads the configuration file and stores to the dom element and during read it replaces the password text node with
    the password passed to it as parameter . After reading whole file it write the whole element to the configuration xml file

    @return 1 if written successfully and zero if any exception occurs
*/

int DduXmlParserClass::WriteConfigurationFile(QString stPassword)
{
    try
    {
        XMLCh *ptrobjTempStr;     // A temporary character pointer to store the password string
#ifdef DEBUG_FLAG
        qDebug()<<"write Configuration file called";
#endif
        const char *ptrcFileName=CONFIG_FILE_PATH;  // A temporary pointer to store the file path
        const XMLCh* ptrobjCurrentText;             // A temporary xmlchar pointer to store the the current text while parsing the document
        DduXmlConfigurationTagNameClass objTagName;    // A temporary object of Configuration tag class having tagnames of configuration file
        XMLCh* ptrobjFilePointer;                   // A char pointer to store the file name
#ifdef DEBUG_FLAG
        qDebug() << "File Name is before parssing " << ptrcFileName<< endl;
        qDebug() << "Ptr value is before transcoding " << ptrobjFilePointer << endl;
#endif
        ptrobjFilePointer = xercesc_2_7::XMLString::transcode(ptrcFileName);
#ifdef DEBUG_FLAG
        qDebug() << "Ptr value is after transcoding " << ptrobjFilePointer << endl;
#endif
        mptrobj_domParser->parse(xercesc_2_7 :: XMLString::transcode(ptrcFileName));
        mptrobj_domParser->parse(ptrobjFilePointer);
        if(mptrobj_domParser->getErrorCount() > gconstValueZero)
        {
#ifdef DEBUG_FLAG
            qDebug() <<ptrcFileName << " file format not valid, parsing unsuccessful" <<endl;
            qDebug() << mptrobj_domParser->getErrorCount() << endl;
#endif
            return gconstValueZero;
        }
        DOMDocument *ptrobjXmlDoc=mptrobj_domParser->getDocument();    // A temporary document pointer to store the reference of the document object of the given file
        XMLString :: release(&ptrobjFilePointer);
        xercesc_2_7 :: DOMElement *ptrobjXmlRoot=ptrobjXmlDoc->getDocumentElement();  // A element pointer to store the root element
        xercesc_2_7 :: DOMNodeList* ptrobjDduConfigParam = ptrobjXmlRoot->getChildNodes();   // A node list pointer to store the all the child nodes of the root element
        const  XMLSize_t objNodeCount = ptrobjDduConfigParam->getLength();          // A size variable to store the no of child node under the root node ** in our case it will be one
        // For all nodes, children of "root" in the XML tree.
        for( XMLSize_t objSecondIndex = gconstValueZero; objSecondIndex < objNodeCount; ++objSecondIndex )
        {
            xercesc_2_7 :: DOMNode* ptrobjCurrentNode = ptrobjDduConfigParam->item(objSecondIndex);    // A temporary node element used to get every childNode object one by one
            if( ptrobjCurrentNode->getNodeType() &&  // true is not NULL
                ptrobjCurrentNode->getNodeType() == xercesc_2_7 ::DOMNode::ELEMENT_NODE ) // is element
            {
                xercesc_2_7 :: DOMElement* ptrobjCurrentElement=(xercesc_2_7::DOMElement*)ptrobjCurrentNode;        // A pointer to store the current element
                if( xercesc_2_7::XMLString::equals(ptrobjCurrentElement->getTagName(), objTagName.mptrobj_tagConfigurationDetails))
                {
#ifdef DEBUG_FLAG
                    qDebug() << __FILE__ << "::" << __FUNCTION__ << "::" << __LINE__ << " Configuration Details:: " << ptrobjCurrentElement->getTagName() <<endl;
#endif
                    xercesc_2_7 :: DOMNodeList* ptrobjChildrens = ptrobjCurrentElement->getChildNodes();       // Store the children of the child node of root that is sub children
                    const  XMLSize_t objChildCount = ptrobjChildrens->getLength();            //  Store the no of childrens
                    for(XMLSize_t objFirstIndex=gconstValueZero;objFirstIndex<objChildCount;objFirstIndex++)
                    {
                        xercesc_2_7 :: DOMNode* ptrobjCurrentNode = ptrobjChildrens->item(objFirstIndex);        // A temporary node element used to get every childNode object one by one
                        if( ptrobjCurrentNode->getNodeType() &&  // true is not NULL
                            ptrobjCurrentNode->getNodeType() == xercesc_2_7 ::DOMNode::ELEMENT_NODE ) // is element
                        {
                            xercesc_2_7 :: DOMElement* ptrobjCurrentElement=(xercesc_2_7::DOMElement*)ptrobjCurrentNode;    // A pointer to store the current element
                            if(xercesc_2_7::XMLString::equals(ptrobjCurrentElement->getTagName(), objTagName.mptrobj_tagParameterUpdationPassword))
                            {
                                ptrobjCurrentText=ptrobjCurrentElement->getTextContent();
#ifdef DEBUG_FLAG
                                qDebug()<<"update Parameter password" << XMLString::transcode(ptrobjCurrentText);
#endif
                                ptrobjCurrentElement->removeChild(ptrobjCurrentElement->getFirstChild());
                                QByteArray objByteArray=stPassword.toLatin1();                              // A byte array used fro converstion fron QString to char *
                                ptrobjTempStr=xercesc_2_7 :: XMLString::transcode(objByteArray.data());
                                mptrobj_textNode = ptrobjXmlDoc->createTextNode(ptrobjTempStr);
                                ptrobjCurrentElement->appendChild(mptrobj_textNode);
                            }

                        }
                    }
                }
            }
        }

#ifdef DEBUG_FLAG
        qDebug()<<"3.Write Configuration XML";       
#endif
        // a CHARACTER ARRAY
        const XMLCh objGLSArray[] = { xercesc_2_7 :: chLatin_L, xercesc_2_7 :: chLatin_S, xercesc_2_7 :: chNull };      // A character array to store the parameters needed for Implementation
        mptrobj_domImplementation = xercesc_2_7 ::DOMImplementationRegistry::getDOMImplementation(objGLSArray);

        mptrobj_theSerializer =((xercesc_2_7 :: DOMImplementationLS*)mptrobj_domImplementation) -> createDOMWriter();
        mptrobj_theSerializer->setFeature(xercesc_2_7 :: XMLUni::fgDOMWRTFormatPrettyPrint, true);
        mptrobj_theSerializer->setEncoding (xercesc_2_7 :: XMLString::transcode("UTF-8"));

        //To create a File

        mptrobj_myFormTarget = new xercesc_2_7 :: LocalFileFormatTarget(ptrcFileName);
        mptrobj_theSerializer->writeNode(mptrobj_myFormTarget,*ptrobjXmlDoc);
        xercesc_2_7::XMLString::release(&ptrobjTempStr);
        delete mptrobj_myFormTarget;//After deletion of this variable, data will be written to file
        mptrobj_theSerializer->release();
        return gconstValueOne;
    }
    catch(xercesc_2_7::XMLException& e)
    {
        char* ptrcErrorMessage = xercesc_2_7::XMLString::transcode(e.getMessage()); // A character pointer to store the error message
#ifdef DEBUG_FLAG
        qDebug() << __FILE__ << "::" << __FUNCTION__ << "::" << __LINE__ <<endl;
        qDebug() << ptrcErrorMessage <<endl;
#endif
        xercesc_2_7::XMLString::release( &ptrcErrorMessage );
        return gconstValueZero;
    }
}

/*
    This function reads the xml file from the specified path and get the route details and fill it into
    the list of route passed to it
    
    @return 1 if successsfully read and 0 if any exception occurs
*/
int DduXmlParserClass::ReadRouteXML(list<DduRouteClass> *ptrobjRouteList,char *ptrcFileName)
{
#ifdef DEBUG_FLAG
    qDebug()<<"3-ReadRouteXML";
#endif
    const XMLCh* ptrobjCurrentText;   // An XML character pointer to hold the value of current tag
    const char* ptrcText=NULL;      // An XML character pointer for the storage of XML string
    DduXmlRouteTagNameClass objTagName;    // An object containing the tag names
    XMLCh* ptrobjFileName;          // An XML character pointer to store the filename
#ifdef DEBUG_FLAG
    qDebug() << "File Name is before parssing " << ptrcFileName<< endl;
    qDebug() << "Ptr value is before transcoding " << ptrobjFileName << endl;
#endif
    ptrobjFileName = xercesc_2_7::XMLString::transcode(ptrcFileName);
#ifdef DEBUG_FLAG
    qDebug() << "Ptr value is after transcoding " << ptrobjFileName << endl;
#endif
    try{
        mptrobj_domParser->parse(ptrobjFileName);
    }
    catch (const XMLException& e) {
        char* ptrcErrorMessage = XMLString::transcode(e.getMessage());  // A character pointer to store the error message
#ifdef DEBUG_FLAG
        qDebug() << "Exception message is: \n"
                << ptrcErrorMessage << "\n";
#endif
        XMLString::release(&ptrcErrorMessage );
        return gconstValueZero;
    }
    catch (const DOMException& e) {
        char* ptrcErrorMessage = XMLString::transcode(e.msg);      // A character pointer to store the error message
#ifdef DEBUG_FLAG
        qDebug() << "Exception message is: \n"
                << ptrcErrorMessage << "\n";
#endif
        XMLString::release(&ptrcErrorMessage );
        return -gconstValueOne;
    }
    catch (...) {
#ifdef DEBUG_FLAG
        qDebug()<< "Unexpected Exception \n" ;
#endif
        return -gconstValueOne;
    }
    if(mptrobj_domParser->getErrorCount() > gconstValueZero)
    {
#ifdef DEBUG_FLAG
        qDebug() <<ptrcFileName << " file format not valid, parsing unsuccessful" <<endl;
        qDebug() << mptrobj_domParser->getErrorCount() << endl;
#endif
        return gconstValueZero;
    }
    try
    {
        DOMDocument *ptrobjXmlDoc=mptrobj_domParser->getDocument();     // A pointer of XML DOC to store the reference of the document to be parsed
        XMLString :: release(&ptrobjFileName);
        xercesc_2_7 :: DOMElement *ptrobjXmlRoot=ptrobjXmlDoc->getDocumentElement();    // A pointer of XML Element to store the reference to the root node of the document
        xercesc_2_7 :: DOMNodeList* ptrobjDduAllRoute = ptrobjXmlRoot->getChildNodes(); // A pointer to store the rference to the lsit of childrens of root
        const  XMLSize_t objNodeCount = ptrobjDduAllRoute->getLength();                 // variable to store the length of the list of childrens

        // For all nodes, children of "root" in the XML tree.
        for( XMLSize_t objSecondIndex = gconstValueZero; objSecondIndex < objNodeCount; ++objSecondIndex )
        {
            xercesc_2_7 :: DOMNode* ptrobjCurrentNode = ptrobjDduAllRoute->item(objSecondIndex);   // A DOMNODE pointer to store the reference to the current node
            if( ptrobjCurrentNode->getNodeType() &&  // true is not NULL
                ptrobjCurrentNode->getNodeType() == xercesc_2_7 ::DOMNode::ELEMENT_NODE ) // is element
            {
                xercesc_2_7 :: DOMElement* ptrobjCurrentElement=(xercesc_2_7::DOMElement*)ptrobjCurrentNode;    // A DOM Element type pointer to store the current element
                if( xercesc_2_7::XMLString::equals(ptrobjCurrentElement->getTagName(), objTagName.mptrobj_tagAllRoutes))
                {
#ifdef DEBUG_FLAG
                    qDebug() << __FILE__ << "::" << __FUNCTION__ << "::" << __LINE__ << " ALL_Routes:: " << ptrobjCurrentElement->getTagName() << endl;
#endif
                    xercesc_2_7 :: DOMNodeList* ptrobjChildren = ptrobjCurrentElement->getChildNodes(); // A pointer to store the rference to the lsit of childrens of sub node of root
                    const  XMLSize_t objChildCount = ptrobjChildren->getLength();                       // variable to store the length of the list of childrens
                    for(XMLSize_t objFirstIndex=gconstValueZero;objFirstIndex<objChildCount;objFirstIndex++)
                    {
                        xercesc_2_7 :: DOMNode* ptrobjCurrentNode = ptrobjChildren->item(objFirstIndex);     // A DOMNODE pointer to store the reference to the current node
                        if( ptrobjCurrentNode->getNodeType() &&  // true is not NULL
                            ptrobjCurrentNode->getNodeType() == xercesc_2_7 ::DOMNode::ELEMENT_NODE ) // is element
                        {
                            xercesc_2_7 :: DOMElement* ptrobjCurrentElement=(xercesc_2_7::DOMElement*)ptrobjCurrentNode;        // A DOM Element type pointer to store the current element
                            if( xercesc_2_7::XMLString::equals(ptrobjCurrentElement->getTagName(), objTagName.mptrobj_tagRoute))
                            {
                                DduRouteClass objRoute;                                                     // A route object
                                list<DduWaypointClass> *ptrobjWaypointlist=new list<DduWaypointClass>();                        // A waypoint list pointer to store the list of waypoint
                                xercesc_2_7 :: DOMNodeList* ptrobjGrandChildren = ptrobjCurrentElement->getChildNodes();         // A pointer to store the rference to the lsit of childrens of NODE
                                const  XMLSize_t objChildCount = ptrobjGrandChildren->getLength();              // A variable to store the length of the list
                                for( XMLSize_t objIndex = gconstValueZero; objIndex < objChildCount; ++objIndex )
                                {
                                    xercesc_2_7 :: DOMNode* ptrobjCurrentNode = ptrobjGrandChildren->item(objIndex);  // A DOMNODE pointer to store the reference to the current node
                                    if( ptrobjCurrentNode->getNodeType() &&  // true is not NULL
                                        ptrobjCurrentNode->getNodeType() == xercesc_2_7 ::DOMNode::ELEMENT_NODE ) // is element
                                    {
                                        xercesc_2_7 :: DOMElement* ptrobjCurrentElement=(xercesc_2_7::DOMElement*)ptrobjCurrentNode;    // A DOM Element type pointer to store the current element
                                        if( xercesc_2_7::XMLString::equals(ptrobjCurrentElement->getTagName(), objTagName.mptrobj_tagName))
                                        {
                                            // Already tested node as type element and of name ""POST
                                            ptrobjCurrentText=ptrobjCurrentElement->getTextContent();
                                            //objFileStore.post=xercesc_2_7::XMLString::transcode(currentText);
                                            objRoute.SetRouteName(xercesc_2_7::XMLString::transcode(ptrobjCurrentText));
                                            QByteArray objByteArray=objRoute.GetRouteName().toLatin1(); // A byte array used for conversion from QString to char *
                                            ptrcText=objByteArray.data();
#ifdef DEBUG_FLAG
                                            qDebug() << __FILE__ << "::" << __FUNCTION__ << "::" << __LINE__ << " ROUTE Name:: " << ptrcText << endl;
#endif
                                        }
                                        if( xercesc_2_7::XMLString::equals(ptrobjCurrentElement->getTagName(), objTagName.mptrobj_tagId))
                                        {
                                            // Already tested node as type element and of name "OFFLINE_TEST"
                                            ptrobjCurrentText=ptrobjCurrentElement->getTextContent();
                                            //                                                    objFileStore.offlineTest=xercesc_2_7::XMLString::transcode(currentText);
                                            objRoute.SetRouteId(QString (xercesc_2_7::XMLString::transcode(ptrobjCurrentText)).toInt());
                                            ptrcText=xercesc_2_7::XMLString::transcode(ptrobjCurrentText);
#ifdef DEBUG_FLAG
                                            qDebug() << __FILE__ << "::" << __FUNCTION__ << "::" << __LINE__ << " ROUTE Id:: " << ptrcText << endl;
#endif
                                        }
                                        if( xercesc_2_7::XMLString::equals(ptrobjCurrentElement->getTagName(), objTagName.mptrobj_tagReferenceWaypointList))
                                        {
                                            //Already tested node as type element and of name ""OUTRIGGERS
                                            ptrobjCurrentText=ptrobjCurrentElement->getTextContent();
                                            //                                                    objFileStore.outriggers=xercesc_2_7::XMLString::transcode(currentText);
                                            //                                                    text=(objFileStore.outriggers).c_str();
                                            QString szTempStr=xercesc_2_7::XMLString::transcode(ptrobjCurrentText);
                                            QStringList objWaypointNamelist;
                                            objWaypointNamelist=szTempStr.split(",");
                                            //                                                list<QString>::iterator WaypointName;
                                            for(int iIndex=gconstValueZero;iIndex<objWaypointNamelist.size();iIndex++)
                                            {
                                                DduWaypointClass objWaypoint;           // A waypoint object to store the values temporarily
                                                objWaypoint.SetWaypointName(objWaypointNamelist.at(iIndex));
                                                ptrobjWaypointlist->push_back(objWaypoint);
                                            }
#ifdef DEBUG_FLAG
                                            qDebug() << __FILE__ << "::" << __FUNCTION__ << "::" << __LINE__ << " WAYPOINT Altitude:: " << ptrcText <<endl;
#endif
                                        }
                                    }
                                }
                                objRoute.SetWaypointlist(ptrobjWaypointlist);
                                ptrobjRouteList->push_back(objRoute);
                            }
                        }
                    }
                }
            }
        }
        return gconstValueOne;
    }
    catch(XMLException& e)
    {
        char* ptrcErrorMessage = xercesc_2_7::XMLString::transcode(e.getMessage()); // A character pointer to store the error message
#ifdef DEBUG_FLAG
        qDebug() << __FILE__ << "::" << __FUNCTION__ << "::" << __LINE__ <<endl;
        qDebug() << ptrcErrorMessage <<endl;
#endif
        xercesc_2_7::XMLString::release( &ptrcErrorMessage );
        return gconstValueZero;
    }
    catch(...)
    {
#ifdef DEBUG_FLAG
        qDebug()<<"UNKNOWN XML EXCEPTION";
#endif
        return gconstValueZero;
    }
}
/*
    This method read the waypoint details from the xml file and fill the waypointlist passes to it as parameter
*/
//Download from PC
int DduXmlParserClass::ReadWaypointXML(list<DduWaypointClass> *ptrobjWaypointList,char *ptrcFileName)
{
#ifdef DEBUG_FLAG
    qDebug()<<"In ReadWaypointXML";
#endif
    QLocale objConversion;      // A QLocale object for conversion
    const XMLCh* ptrobjCurrentText;       // An XML character pointer to hold the value of current tag
    const char* ptrcText=NULL;          // An XML character pointer for the storage of XML string
    DduXmlWaypointTagNameClass objTagName;  // An object containing the tag names
    XMLCh* ptrobjFileName;              // An XML character pointer to store the filename
#ifdef DEBUG_FLAG
    qDebug() << "File Name is before parssing " << ptrcFileName<< endl;
    qDebug() << "Ptr value is before transcoding " << ptrobjFileName << endl;
#endif
    try
    {
        ptrobjFileName = xercesc_2_7::XMLString::transcode(ptrcFileName);
#ifdef DEBUG_FLAG
        qDebug() << "Ptr value is after transcoding " << ptrobjFileName << endl;
#endif
        mptrobj_domParser->parse(ptrobjFileName);
        if(mptrobj_domParser->getErrorCount() > gconstValueZero)
        {
#ifdef DEBUG_FLAG
            qDebug() <<ptrcFileName << " file format not valid, parsing unsuccessful" <<endl;
            qDebug() << mptrobj_domParser->getErrorCount() << endl;
#endif
            return gconstValueZero;
        }
        DOMDocument *ptrobjXmlDoc=mptrobj_domParser->getDocument();     // A pointer of XML DOC to store the reference of the document to be parsed
        XMLString :: release(&ptrobjFileName);
        xercesc_2_7 :: DOMElement *ptrobjXmlRoot=ptrobjXmlDoc->getDocumentElement();    // A pointer of XML Element to store the reference to the root node of the document
        xercesc_2_7 :: DOMNodeList* ptrobjDduAllWaypoint = ptrobjXmlRoot->getChildNodes(); // A pointer to store the rference to the lsit of childrens of root
        const  XMLSize_t objNodeCount = ptrobjDduAllWaypoint->getLength();        // variable to store the length of the list of childrens

        // For all nodes, children of "root" in the XML tree.
        for( XMLSize_t objSecondIndex = gconstValueZero; objSecondIndex < objNodeCount; ++objSecondIndex )
        {
            xercesc_2_7 :: DOMNode* ptrobjCurrentNode = ptrobjDduAllWaypoint->item(objSecondIndex);    // A DOMNODE pointer to store the reference to the current node
            if( ptrobjCurrentNode->getNodeType() &&  // true is not NULL
                ptrobjCurrentNode->getNodeType() == xercesc_2_7 ::DOMNode::ELEMENT_NODE ) // is element
            {
                xercesc_2_7 :: DOMElement* ptrobjCurrentElement=(xercesc_2_7::DOMElement*)ptrobjCurrentNode;  // A DOM Element type pointer to store the current element
                if( xercesc_2_7::XMLString::equals(ptrobjCurrentElement->getTagName(), objTagName.mptrobj_tagAllWaypoints))
                {
#ifdef DEBUG_FLAG
                    qDebug() << __FILE__ << "::" << __FUNCTION__ << "::" << __LINE__ << " ALL_waypoints:: " << ptrobjCurrentElement->getTagName() <<endl;
#endif
                    xercesc_2_7 :: DOMNodeList* ptrobjChildren = ptrobjCurrentElement->getChildNodes(); // A pointer to store the rference to the lsit of childrens of node
                    const  XMLSize_t objChildCount = ptrobjChildren->getLength();            // variable to store the length of the list of childrens
                    for(XMLSize_t objfirstIndex=gconstValueZero;objfirstIndex<objChildCount;objfirstIndex++)
                    {
                        xercesc_2_7 :: DOMNode* ptrobjCurrentNode = ptrobjChildren->item(objfirstIndex);    // A DOMNODE pointer to store the reference to the current node
                        if( ptrobjCurrentNode->getNodeType() &&  // true is not NULL
                            ptrobjCurrentNode->getNodeType() == xercesc_2_7 ::DOMNode::ELEMENT_NODE ) // is element
                        {
                            xercesc_2_7 :: DOMElement* ptrobjCurrentElement=(xercesc_2_7::DOMElement*)ptrobjCurrentNode;        // A DOM Element type pointer to store the current element
                            if( xercesc_2_7::XMLString::equals(ptrobjCurrentElement->getTagName(), objTagName.mptrobj_tagWaypoint))
                            {
                                DduWaypointClass objWaypoint;                                           // A waypoint object
                                DduLocationClass objLocation;                                           // A location object
                                xercesc_2_7 :: DOMNodeList* ptrobjGrandChildren = ptrobjCurrentElement->getChildNodes();  // A pointer to store the rference to the lsit of childrens of node
                                const  XMLSize_t objChildCount = ptrobjGrandChildren->getLength();                   // variable to store the length of the list of childrens
                                for( XMLSize_t objIndex = gconstValueZero; objIndex < objChildCount; ++objIndex )
                                {

                                    xercesc_2_7 :: DOMNode* ptrobjcurrentNode = ptrobjGrandChildren->item(objIndex);  // A DOMNODE pointer to store the reference to the current node
                                    if( ptrobjcurrentNode->getNodeType() &&  // true is not NULL
                                        ptrobjcurrentNode->getNodeType() == xercesc_2_7 ::DOMNode::ELEMENT_NODE ) // is element
                                    {
                                        xercesc_2_7 :: DOMElement* ptrobjcurrentElement=(xercesc_2_7::DOMElement*)ptrobjcurrentNode;    // A DOM Element type pointer to store the current element
                                        if( xercesc_2_7::XMLString::equals(ptrobjcurrentElement->getTagName(), objTagName.mptrobj_tagName))
                                        {
                                            // Already tested node as type element and of name ""POST
                                            ptrobjCurrentText=ptrobjcurrentElement->getTextContent();
                                            //objFileStore.post=xercesc_2_7::XMLString::transcode(currentText);
                                            objWaypoint.SetWaypointName(xercesc_2_7::XMLString::transcode(ptrobjCurrentText));
                                            QByteArray objByteArray=objWaypoint.GetWaypointName().toLatin1();       // A byte array for conversion from string to char *
                                            ptrcText=objByteArray.data();
#ifdef DEBUG_FLAG
                                            qDebug() << __FILE__ << "::" << __FUNCTION__ << "::" << __LINE__ << " WAYPOINT Name:: " << ptrcText <<endl;
#endif
                                        }
                                        if( xercesc_2_7::XMLString::equals(ptrobjcurrentElement->getTagName(), objTagName.mptrobj_tagZone))
                                        {
                                            // Already tested node as type element and of name "OFFLINE_TEST"
                                            ptrobjCurrentText=ptrobjcurrentElement->getTextContent();
                                            //                                                    objFileStore.offlineTest=xercesc_2_7::XMLString::transcode(currentText);
                                            objLocation.SetZone(xercesc_2_7::XMLString::transcode(ptrobjCurrentText));
                                            ptrcText=xercesc_2_7::XMLString::transcode(ptrobjCurrentText);
#ifdef DEBUG_FLAG
                                            qDebug() << __FILE__ << "::" << __FUNCTION__ << "::" << __LINE__ << " WAYPOINT Zone:: " << ptrcText <<endl;
#endif
                                        }
                                        if( xercesc_2_7::XMLString::equals(ptrobjcurrentElement->getTagName(), objTagName.mptrobj_tagAltitude))
                                        {
                                            //Already tested node as type element and of name ""OUTRIGGERS
                                            ptrobjCurrentText=ptrobjcurrentElement->getTextContent();
                                            //                                                    objFileStore.outriggers=xercesc_2_7::XMLString::transcode(currentText);
                                            //                                                    text=(objFileStore.outriggers).c_str();
                                            objLocation.SetAltitude(QString( xercesc_2_7::XMLString::transcode(ptrobjCurrentText) ).toDouble());
                                            ptrcText=xercesc_2_7::XMLString::transcode(ptrobjCurrentText);
#ifdef DEBUG_FLAG
                                            qDebug() << __FILE__ << "::" << __FUNCTION__ << "::" << __LINE__ << " WAYPOINT Altitude:: " << ptrcText <<endl;
#endif
                                        }
                                        if( xercesc_2_7::XMLString::equals(ptrobjcurrentElement->getTagName(), objTagName.mptrobj_tagNorth))
                                        {
                                            //Already tested node as type element and of name ""TILTING
                                            ptrobjCurrentText=ptrobjcurrentElement->getTextContent();
                                            //                                                    objFileStore.articulation=xercesc_2_7::XMLString::transcode(currentText);
                                            //                                                    text=(objFileStore.articulation).c_str();
                                            objLocation.SetNorth(QString( xercesc_2_7::XMLString::transcode(ptrobjCurrentText) ).toDouble());
                                            ptrcText=xercesc_2_7::XMLString::transcode(ptrobjCurrentText);
#ifdef DEBUG_FLAG
                                            qDebug() << __FILE__ << "::" << __FUNCTION__ << "::" << __LINE__ << " WAYPOINT North:: " << ptrcText <<endl;
#endif
                                        }
                                        if( xercesc_2_7::XMLString::equals(ptrobjcurrentElement->getTagName(), objTagName.mptrobj_tagEast))
                                        {
                                            ptrobjCurrentText=ptrobjcurrentElement->getTextContent();
                                            //                                                    objFileStore.sliding=xercesc_2_7::XMLString::transcode(currentText);
                                            //                                                    text=(objFileStore.sliding).c_str();
                                            objLocation.SetEast( QString( xercesc_2_7::XMLString::transcode(ptrobjCurrentText) ).toDouble());
                                            ptrcText=xercesc_2_7::XMLString::transcode(ptrobjCurrentText);
#ifdef DEBUG_FLAG
                                            qDebug() << __FILE__ << "::" << __FUNCTION__ << "::" << __LINE__ << " WAYPOINT East:: " << ptrcText <<endl;
#endif
                                        }
                                    }
                                }
                                objWaypoint.SetLocation(objLocation);
                                ptrobjWaypointList->push_back(objWaypoint);
#ifdef DEBUG_FLAG
                                list<DduWaypointClass>::iterator WaypointOne;
                                for(WaypointOne=ptrobjWaypointList->begin();WaypointOne!=ptrobjWaypointList->end();WaypointOne++)
                                {
                                    qDebug()<<"WAYPOINT :"<<WaypointOne->GetWaypointName();
                                    //qDebug()<<Waypoint1->mobj_dduLocationClass.Getzone();

                                }
#endif
                            }
                        }
                    }
                }
            }
        }
        return gconstValueOne;
    }
    catch(XMLException& e)
    {
        char* ptrcErrorMessage = xercesc_2_7::XMLString::transcode(e.getMessage()); // A character pointer to store the error message
#ifdef DEBUG_FLAG
        qDebug() << __FILE__ << "::" << __FUNCTION__ << "::" << __LINE__ <<endl;
        qDebug() << ptrcErrorMessage <<endl;
#endif
        xercesc_2_7::XMLString::release( &ptrcErrorMessage );
        return gconstValueZero;
    }
    catch(...)
    {
#ifdef DEBUG_FLAG
        qDebug()<<"UNKNOWN XML EXCEPTION";
#endif
        return gconstValueZero;
    }
}

/*
    This function gets the route details from the list passed to it as parameter
    and then write the route details to the specified xml file passed to it as parameter
*/

int DduXmlParserClass::WriteRouteXML(list<DduRouteClass> *ptrobjRouteList,char *ptrcFileName)
{
#ifdef DEBUG_FLAG
    qDebug()<<"3.Write Route XML";
#endif
    DduXmlRouteTagNameClass objTagName;                 // An object containing the tag names
    XMLCh *ptrobjTempStr;                               // An XML character pointer to store the temporary strings
    list<DduRouteClass>::iterator objRouteIterator;     // an iterator object of routelist to iterate through the list
    try
    {
        // a CHARACTER ARRAY
        const XMLCh objGLSArray[] = { xercesc_2_7 :: chLatin_L, xercesc_2_7 :: chLatin_S, xercesc_2_7 :: chNull };
        mptrobj_domImplementation = xercesc_2_7 ::DOMImplementationRegistry::getDOMImplementation(objGLSArray);

        mptrobj_theSerializer =((xercesc_2_7 :: DOMImplementationLS*)mptrobj_domImplementation) -> createDOMWriter();
        mptrobj_theSerializer->setFeature(xercesc_2_7 :: XMLUni::fgDOMWRTFormatPrettyPrint, true);
        mptrobj_theSerializer->setEncoding (xercesc_2_7 :: XMLString::transcode("UTF-8"));

        //To create a File

        mptrobj_myFormTarget = new xercesc_2_7 :: LocalFileFormatTarget(ptrcFileName);

        //To register the document with DOM structure
        mptrobj_domImplementation = xercesc_2_7 :: DOMImplementationRegistry::getDOMImplementation(objTagName.mptrobj_tagRange);
        mptrobj_domDocument=mptrobj_domImplementation->createDocument(gconstValueZero,objTagName.mptrobj_tagRouteDetails,gconstValueZero);
        mptrobj_rootElement = mptrobj_domDocument->getDocumentElement();
        xercesc_2_7 :: DOMElement*  ptrobjElementParent = mptrobj_domDocument->createElement(objTagName.mptrobj_tagAllRoutes);  // A pointer to refer an element
        mptrobj_rootElement->appendChild(ptrobjElementParent);

        for(objRouteIterator=ptrobjRouteList->begin();objRouteIterator!=ptrobjRouteList->end();objRouteIterator++)
        {

            xercesc_2_7 :: DOMElement*  ptrobjSubElemParent = mptrobj_domDocument->createElement(objTagName.mptrobj_tagRoute);    // Dom elemet object to be added to the file
            ptrobjElementParent->appendChild(ptrobjSubElemParent);

            xercesc_2_7 :: DOMElement*  ptrobjElementOne = mptrobj_domDocument->createElement(objTagName.mptrobj_tagId);        // Dom elemet object to be added to the file
            ptrobjSubElemParent->appendChild(ptrobjElementOne);
            QByteArray objByteArray=QString ::number(objRouteIterator->GetRouteId()).toLatin1();        // Used for conversion from QString to char *
            ptrobjTempStr=xercesc_2_7 :: XMLString::transcode(objByteArray.data());
            mptrobj_textNode = mptrobj_domDocument->createTextNode(ptrobjTempStr);
            ptrobjElementOne->appendChild(mptrobj_textNode);

            xercesc_2_7 :: DOMElement*  ptrobjElementTwo = mptrobj_domDocument->createElement(objTagName.mptrobj_tagName);  // Dom elemet object to be added to the file
            ptrobjSubElemParent->appendChild(ptrobjElementTwo);
            objByteArray=objRouteIterator->GetRouteName().toLatin1();
            ptrobjTempStr=xercesc_2_7 :: XMLString::transcode(objByteArray.data());
            mptrobj_textNode = mptrobj_domDocument->createTextNode(ptrobjTempStr);
            ptrobjElementTwo->appendChild(mptrobj_textNode);

            xercesc_2_7 :: DOMElement*  ptrobjElementThree = mptrobj_domDocument->createElement(objTagName.mptrobj_tagReferenceWaypointList);   // Dom elemet object to be added to the file
            ptrobjSubElemParent->appendChild(ptrobjElementThree);
            list<DduWaypointClass>::iterator objWaypointIterator;               // A iterator object to iterate through the list of waypoints
            list<DduWaypointClass> *ptrobjWaypointList=objRouteIterator->GetWaypointList(); // A pointer to the waypoint list
            QString szString=NULL;      // A temporary string to keep the list of waypoint name
            for(objWaypointIterator=ptrobjWaypointList->begin();objWaypointIterator!=ptrobjWaypointList->end();objWaypointIterator++)
            {
#ifdef DEBUG_FLAG
                qDebug()<<ptrobjWaypointList->begin()->GetWaypointName();
#endif
                if(szString==NULL)
                    szString = objWaypointIterator->GetWaypointName();//segmentation fault
                else
                    szString +=","+objWaypointIterator->GetWaypointName();
            }
            objByteArray=szString.toLatin1();
            ptrobjTempStr=xercesc_2_7 :: XMLString::transcode(objByteArray.data());
            mptrobj_textNode = mptrobj_domDocument->createTextNode(ptrobjTempStr);
            ptrobjElementThree->appendChild(mptrobj_textNode);

        }
        //this is used for write the waypoint into xml file
        mptrobj_theSerializer->writeNode(mptrobj_myFormTarget, *mptrobj_domDocument);
        xercesc_2_7::XMLString::release(&ptrobjTempStr);
        delete mptrobj_myFormTarget;//After deletion of this variable, data will be written to file
        mptrobj_theSerializer->release();
        return gconstValueOne;
    }
    catch(xercesc_2_7::XMLException& e)
    {
        char* ptrcErrorMessage = xercesc_2_7::XMLString::transcode(e.getMessage());     // A character pointer to store the error message
#ifdef DEBUG_FLAG
        qDebug() << __FILE__ << "::" << __FUNCTION__ << "::" << __LINE__ <<endl;
        qDebug() << ptrcErrorMessage <<endl;
#endif
        xercesc_2_7::XMLString::release( &ptrcErrorMessage );


        return gconstValueZero;
    }
}

/*
    This function gets the waypoint details from the list passed to it as parameter
    and then write the waypoint details to the specified xml file passed to it as parameter
*/


int DduXmlParserClass::WriteWaypointXML(list<DduWaypointClass> *ptrobjWaypointList,char *ptrcFileName)
{




    DduXmlWaypointTagNameClass objTagName; // An object cantaining the tagnames to be used

    XMLCh *ptrobjTempStr;           // A XML character pointer to store the strings temporarily
    list<DduWaypointClass>::iterator objWaypointIterator;   // A iterator object to itrerate through the list of waypoints
    try
    {
        // a CHARACTER ARRAY
        const XMLCh objGLSArray[] = { xercesc_2_7 :: chLatin_L, xercesc_2_7 :: chLatin_S, xercesc_2_7 :: chNull };
        mptrobj_domImplementation = xercesc_2_7 ::DOMImplementationRegistry::getDOMImplementation(objGLSArray);

        mptrobj_theSerializer =((xercesc_2_7 :: DOMImplementationLS*)mptrobj_domImplementation) -> createDOMWriter();
        mptrobj_theSerializer->setFeature(xercesc_2_7 :: XMLUni::fgDOMWRTFormatPrettyPrint, true);
        mptrobj_theSerializer->setEncoding (xercesc_2_7 :: XMLString::transcode("UTF-8"));

        //To create a File
        XMLCh* ptrobjTempFNam=xercesc_2_7::XMLString::transcode(ptrcFileName);        // A temporary variable to store the file name
        mptrobj_myFormTarget = new xercesc_2_7 :: LocalFileFormatTarget(ptrobjTempFNam);

        //To register the document with DOM structure
#ifdef DEBUG_FLAG
        qDebug()<<objTagName.mptrobj_tagWaypointDetails;
#endif
        mptrobj_domImplementation = xercesc_2_7 :: DOMImplementationRegistry::getDOMImplementation(objTagName.mptrobj_tagRange);
#ifdef DEBUG_FLAG
        qDebug()<<mptrobj_domImplementation;
#endif
        mptrobj_domDocument=mptrobj_domImplementation->createDocument(gconstValueZero,objTagName.mptrobj_tagWaypointDetails,gconstValueZero);
        mptrobj_rootElement = mptrobj_domDocument->getDocumentElement();
        xercesc_2_7 :: DOMElement*  ptrobjParentElement = mptrobj_domDocument->createElement(objTagName.mptrobj_tagAllWaypoints);   // An object of the parent node of the document
        mptrobj_rootElement->appendChild(ptrobjParentElement);
        //int i=0;
        for(objWaypointIterator=ptrobjWaypointList->begin();objWaypointIterator!=ptrobjWaypointList->end();objWaypointIterator++)
        {

            xercesc_2_7 :: DOMElement*  ptrobjSubElemParent = mptrobj_domDocument->createElement(objTagName.mptrobj_tagWaypoint);   // An object of the element
            ptrobjParentElement->appendChild(ptrobjSubElemParent);

            xercesc_2_7 :: DOMElement*  ptrobjElementZero = mptrobj_domDocument->createElement(objTagName.mptrobj_tagName); // An object of the element
            ptrobjSubElemParent->appendChild(ptrobjElementZero);
            //-----ba define
            QByteArray objByteArray=objWaypointIterator->GetWaypointName().toLatin1();  // byte array used for conversion from QString to char *
            ptrobjTempStr=xercesc_2_7 :: XMLString::transcode(objByteArray.data());
            mptrobj_textNode = mptrobj_domDocument->createTextNode(ptrobjTempStr);
            ptrobjElementZero->appendChild(mptrobj_textNode);
            //            DduWaypointClass o;
            //            o.mobj_dduLocationClass.GetZone();
            xercesc_2_7 :: DOMElement*  ptrobjelementOne = mptrobj_domDocument->createElement(objTagName.mptrobj_tagZone);  // An object of the element
            ptrobjSubElemParent->appendChild(ptrobjelementOne);
            //-----------------
#ifdef DEBUG_FLAG
            qDebug()<<QString::number(objWaypointIterator->GetLocation()->GetZone()).toLatin1();
#endif

            objByteArray = objWaypointIterator->GetLocation()->GetZone();
            ptrobjTempStr=xercesc_2_7 :: XMLString::transcode(objByteArray.data());
            mptrobj_textNode = mptrobj_domDocument->createTextNode(ptrobjTempStr);
            ptrobjelementOne->appendChild(mptrobj_textNode);

            xercesc_2_7 :: DOMElement*  ptrobjElementTwo = mptrobj_domDocument->createElement(objTagName.mptrobj_tagAltitude);  // An object of the element
            ptrobjSubElemParent->appendChild(ptrobjElementTwo);
            objByteArray=QString::number( objWaypointIterator->GetLocation()->GetAltitude(), 'f', gconstValueFive ).toLatin1();
            ptrobjTempStr=xercesc_2_7 :: XMLString::transcode(objByteArray.data());
            mptrobj_textNode = mptrobj_domDocument->createTextNode(ptrobjTempStr);
            ptrobjElementTwo->appendChild(mptrobj_textNode);

            xercesc_2_7 :: DOMElement*  ptrobjElementThree = mptrobj_domDocument->createElement(objTagName.mptrobj_tagEast);    // An object of the element
            ptrobjSubElemParent->appendChild(ptrobjElementThree);
            objByteArray=QString::number( objWaypointIterator->GetLocation()->GetNorth(), 'f', gconstValueFive ).toLatin1();
            ptrobjTempStr=xercesc_2_7 :: XMLString::transcode(objByteArray.data());
            mptrobj_textNode = mptrobj_domDocument->createTextNode(ptrobjTempStr);
            ptrobjElementThree->appendChild(mptrobj_textNode);

            xercesc_2_7 :: DOMElement*  ptrobjElementFour = mptrobj_domDocument->createElement(objTagName.mptrobj_tagNorth);    // An object of the element
            ptrobjSubElemParent->appendChild(ptrobjElementFour);
            objByteArray=QString::number( objWaypointIterator->GetLocation()->GetEast(), 'f', gconstValueFive ).toLatin1();
            ptrobjTempStr=xercesc_2_7 :: XMLString::transcode(objByteArray.data());
            mptrobj_textNode = mptrobj_domDocument->createTextNode(ptrobjTempStr);
            ptrobjElementFour->appendChild(mptrobj_textNode);
            //i++;
            count++;
            //            emit demo1(i);

        }
        //this is used for write the waypoint into xml file
        mptrobj_theSerializer->writeNode(mptrobj_myFormTarget, *mptrobj_domDocument);
        xercesc_2_7::XMLString::release(&ptrobjTempStr);
        delete mptrobj_myFormTarget;//After deletion of this variable, data will be written to file
        xercesc_2_7::XMLString::release(&ptrobjTempFNam);
        mptrobj_theSerializer->release();
        return gconstValueOne;
    }
    catch(xercesc_2_7::XMLException& e)
    {
        char* ptrcErrorMessage = xercesc_2_7::XMLString::transcode(e.getMessage());     // A character pointer to store the error message
#ifdef DEBUG_FLAG
        qDebug() << __FILE__ << "::" << __FUNCTION__ << "::" << __LINE__ <<endl;
        qDebug() << ptrcErrorMessage <<endl;
#endif
        xercesc_2_7::XMLString::release( &ptrcErrorMessage );
        exit(EXIT_FAILURE);
        return gconstValueZero;
    }
    catch (...)
    {
#ifdef DEBUG_FLAG
        qDebug() << "Unexpected Exception \n" ;
#endif
        return -gconstValueOne;
    }
}
int DduXmlParserClass::DemoOne()
{
    return this->count;
}
void DduXmlParserClass::Progress()
{
    //DduDownloadUploadScreenClass *obj_dduDownloadUploadScreenClass=new DduDownloadUploadScreenClass();

}
