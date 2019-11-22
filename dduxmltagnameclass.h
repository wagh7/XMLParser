#ifndef DDUXMLTAGNAMECLASS_H
#define DDUXMLTAGNAMECLASS_H

#include<xercesc/dom/DOMImplementation.hpp>
#include<xercesc/parsers/XercesDOMParser.hpp>
#include<iostream>

class DduXmlTagNameClass
{
public:
    DduXmlTagNameClass();
    ~DduXmlTagNameClass();
};
class DduXmlRouteTagNameClass
{
public:
    DduXmlRouteTagNameClass();
    ~DduXmlRouteTagNameClass();
    XMLCh* mptrobj_tagRange;            // A member variable of type Xml char pointer to store the tagname Range
    XMLCh* mptrobj_tagRouteDetails;     // A member variable of type Xml char pointer to store the tagnames RouteDetails
    XMLCh* mptrobj_tagAllRoutes;        // A member variable of type Xml char pointer to store the tagname ALL Route
    XMLCh* mptrobj_tagRoute;            // A member variable of type Xml char pointer to store the tagname Route
    XMLCh* mptrobj_tagId;               // A member variable of type Xml char pointer to store the tagname Route id
    XMLCh* mptrobj_tagName;             // A member variable of type Xml char pointer to store the tagnames Route Name
    XMLCh* mptrobj_tagReferenceWaypointList;    // A member variable of type Xml char pointer to store the tagname Waypoint list

};
class DduXmlWaypointTagNameClass
{
public:
    DduXmlWaypointTagNameClass();
    ~DduXmlWaypointTagNameClass();
    XMLCh* mptrobj_tagRange;            // A member variable of type Xml char pointer to store the tagname  Range
    XMLCh* mptrobj_tagWaypointDetails;  // A member variable of type Xml char pointer to store the tagname  Waypoint Details
    XMLCh* mptrobj_tagAllWaypoints;     // A member variable of type Xml char pointer to store the tagname  AllWaypoint
    XMLCh* mptrobj_tagWaypoint;         // A member variable of type Xml char pointer to store the tagname  Waypoint
    XMLCh* mptrobj_tagName;             // A member variable of type Xml char pointer to store the tagname  Name
    XMLCh* mptrobj_tagZone;             // A member variable of type Xml char pointer to store the tagname  Zone
    XMLCh* mptrobj_tagAltitude;         // A member variable of type Xml char pointer to store the tagname  Altitude
    XMLCh* mptrobj_tagEast;             // A member variable of type Xml char pointer to store the tagname  East
    XMLCh* mptrobj_tagNorth;            // A member variable of type Xml char pointer to store the tagname  North
};


class DduXmlConfigurationTagNameClass
{
public:
    DduXmlConfigurationTagNameClass();
    ~DduXmlConfigurationTagNameClass();
    XMLCh *mptrobj_tagConfigurationDetails;     // A member variable of type Xml char pointer to store the tagname Configuration Detail
    XMLCh *mptrobj_tagDatabaseName;             // A member variable of type Xml char pointer to store the tagname Database Name
    XMLCh *mptrobj_tagDatabaseUserName;         // A member variable of type Xml char pointer to store the tagname Database User Name
    XMLCh *mptrobj_tagDatabasePassword;         // A member variable of type Xml char pointer to store the tagname Database password
    XMLCh *mptrobj_tagHeading;                  // A member variable of type Xml char pointer to store the tagname Heading
    XMLCh *mptrobj_tagDatumId;                  // A member variable of type Xml char pointer to store the tagname Map Datum
    XMLCh * mptrobj_tagReferenceSystem;         // A member variable of type Xml char pointer to store the tagname Co-ordinate reference system
    XMLCh *mptrobj_tagParameterUpdationPassword;// A member variable of type Xml char pointer to store the tagname Parameter Updation password
};
#endif // DDUXMLTAGNAMECLASS_H


