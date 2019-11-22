#include "dduxmltagnameclass.h"

DduXmlTagNameClass::DduXmlTagNameClass()
{

}

DduXmlTagNameClass::~DduXmlTagNameClass()
{

}

DduXmlWaypointTagNameClass::DduXmlWaypointTagNameClass():
    mptrobj_tagRange(xercesc_2_7::XMLString::transcode("Range")),
    mptrobj_tagWaypointDetails(xercesc_2_7::XMLString::transcode("WAYPOINT_DETAILS")),
    mptrobj_tagAllWaypoints(xercesc_2_7::XMLString::transcode("ALL_WAYPOINTS")),
    mptrobj_tagWaypoint(xercesc_2_7::XMLString::transcode("WAYPOINT")),
    mptrobj_tagName(xercesc_2_7::XMLString::transcode("NAME")),
    mptrobj_tagZone(xercesc_2_7::XMLString::transcode("ZONE")),
    mptrobj_tagAltitude(xercesc_2_7::XMLString::transcode("ALTITUDE")),
    mptrobj_tagEast(xercesc_2_7::XMLString::transcode("EAST")),
    mptrobj_tagNorth(xercesc_2_7::XMLString::transcode("NORTH"))
    {

    }

DduXmlWaypointTagNameClass::~DduXmlWaypointTagNameClass()
{
        try
        {
                xercesc_2_7::XMLString::release(&mptrobj_tagRange);
                xercesc_2_7::XMLString::release(&mptrobj_tagWaypointDetails);
                xercesc_2_7::XMLString::release(&mptrobj_tagAllWaypoints);
                xercesc_2_7::XMLString::release(&mptrobj_tagWaypoint);
                xercesc_2_7::XMLString::release(&mptrobj_tagZone);
                xercesc_2_7::XMLString::release(&mptrobj_tagAltitude);
                xercesc_2_7::XMLString::release(&mptrobj_tagEast);
                xercesc_2_7::XMLString::release(&mptrobj_tagNorth);
                xercesc_2_7::XMLString::release(&mptrobj_tagName);
        }catch(...)
        {
#ifdef DEBUG_FLAG
                qDebug() << __FILE__ << "::" << __FUNCTION__ << "::" << __LINE__ << std :: endl;
                qDebug()<< "Unknown exception..!" << std ::endl;
#endif
                exit(EXIT_FAILURE);

        }
}

DduXmlRouteTagNameClass::DduXmlRouteTagNameClass():
        mptrobj_tagRange(xercesc_2_7::XMLString::transcode("Range")),
        mptrobj_tagRouteDetails(xercesc_2_7::XMLString::transcode("ROUTE_DETAILS")),
        mptrobj_tagAllRoutes(xercesc_2_7::XMLString::transcode("ALL_ROUTES")),
        mptrobj_tagRoute(xercesc_2_7::XMLString::transcode("ROUTE")),
        mptrobj_tagId(xercesc_2_7::XMLString::transcode("ID")),
        mptrobj_tagName(xercesc_2_7::XMLString::transcode("NAME")),
        mptrobj_tagReferenceWaypointList(xercesc_2_7::XMLString::transcode("REFERENCE_WAYPOINT_LIST"))
    {

    }

DduXmlRouteTagNameClass::~DduXmlRouteTagNameClass()
{
        try
        {
                xercesc_2_7::XMLString::release(&mptrobj_tagRange);
                xercesc_2_7::XMLString::release(&mptrobj_tagRouteDetails);
                xercesc_2_7::XMLString::release(&mptrobj_tagAllRoutes);
                xercesc_2_7::XMLString::release(&mptrobj_tagRoute);
                xercesc_2_7::XMLString::release(&mptrobj_tagId);
                xercesc_2_7::XMLString::release(&mptrobj_tagName);
                xercesc_2_7::XMLString::release(&mptrobj_tagReferenceWaypointList);
        }catch(...)
        {
            #ifdef DEBUG_FLAG
                qDebug() << __FILE__ << "::" << __FUNCTION__ << "::" << __LINE__ << std :: endl;
                qDebug() << "Unknown exception..!" << std ::endl;
#endif
                exit(EXIT_FAILURE);

        }
}


DduXmlConfigurationTagNameClass::DduXmlConfigurationTagNameClass():
    mptrobj_tagConfigurationDetails(xercesc_2_7::XMLString::transcode("CONFIGURATION_DETAILS")),
    mptrobj_tagDatabaseName(xercesc_2_7::XMLString::transcode("DATABASE_NAME")),
    mptrobj_tagDatabaseUserName(xercesc_2_7::XMLString::transcode("DATABASE_USER_NAME")),
    mptrobj_tagDatabasePassword(xercesc_2_7::XMLString::transcode("DATABASE_PASSWORD")),
    mptrobj_tagHeading(xercesc_2_7::XMLString::transcode("HEADING")),
    mptrobj_tagDatumId(xercesc_2_7::XMLString::transcode("DATUM_ID")),
    mptrobj_tagReferenceSystem(xercesc_2_7::XMLString::transcode("REFERENCE_SYSTEM")),
    mptrobj_tagParameterUpdationPassword(xercesc_2_7::XMLString::transcode("PARAMETER_UPDATION_PASSWORD"))
    {

    }

DduXmlConfigurationTagNameClass::~DduXmlConfigurationTagNameClass()
{
    try
    {
            xercesc_2_7::XMLString::release(&mptrobj_tagConfigurationDetails);
            xercesc_2_7::XMLString::release(&mptrobj_tagDatabaseName);
            xercesc_2_7::XMLString::release(&mptrobj_tagDatabasePassword);
            xercesc_2_7::XMLString::release(&mptrobj_tagDatabaseUserName);
            xercesc_2_7::XMLString::release(&mptrobj_tagDatumId);
            xercesc_2_7::XMLString::release(&mptrobj_tagReferenceSystem);
            xercesc_2_7::XMLString::release(&mptrobj_tagParameterUpdationPassword);
    }catch(...)
    {
        #ifdef DEBUG_FLAG
            qDebug() << __FILE__ << "::" << __FUNCTION__ << "::" << __LINE__ << std :: endl;
            qDebug() << "Unknown exception..!" << std ::endl;
#endif
            exit(EXIT_FAILURE);

    }
}

/*---------

DDUXMLWaypointTagNames::DDUXMLWaypointTagNames():
    TAG_RANGE(xercesc_2_7::XMLString::transcode("Range")),
    TAG_WAYPOINT_DETAILS(xercesc_2_7::XMLString::transcode("WAYPOINT_DETAILS")),
    TAG_ALL_WAYPOINTS(xercesc_2_7::XMLString::transcode("ALL_WAYPOINTS")),
    TAG_WAYPOINT(xercesc_2_7::XMLString::transcode("WAYPOINT")),
    TAG_ZONE(xercesc_2_7::XMLString::transcode("ZONE")),
    TAG_ALTITUDE(xercesc_2_7::XMLString::transcode("ALTITUDE")),
    TAG_EAST(xercesc_2_7::XMLString::transcode("EAST")),
    TAG_NORTH(xercesc_2_7::XMLString::transcode("NORTH")),
    TAG_NAME(xercesc_2_7::XMLString::transcode("NAME"))
    {

    }

DDUXMLWaypointTagNames::~DDUXMLWaypointTagNames()
{
        try
        {
                xercesc_2_7::XMLString::release(&TAG_RANGE);
                xercesc_2_7::XMLString::release(&TAG_WAYPOINT_DETAILS);
                xercesc_2_7::XMLString::release(&TAG_ALL_WAYPOINTS);
                xercesc_2_7::XMLString::release(&TAG_WAYPOINT);
                xercesc_2_7::XMLString::release(&TAG_ZONE);
                xercesc_2_7::XMLString::release(&TAG_ALTITUDE);
                xercesc_2_7::XMLString::release(&TAG_EAST);
                xercesc_2_7::XMLString::release(&TAG_NORTH);
                xercesc_2_7::XMLString::release(&TAG_NAME);
        }catch(...)
        {
                qDebug() << __FILE__ << "::" << __FUNCTION__ << "::" << __LINE__ << std :: endl;
                qDebug() << "Unknown exception..!" << std ::endl;
                exit(EXIT_FAILURE);

        }
}


  */
