<?xml version="1.0" encoding="UTF-8"?>
<tileset version="1.11" tiledversion="1.11.1" name="kitsune-tail" tilewidth="16" tileheight="16" tilecount="4" columns="4" objectalignment="right">
 <image source="kitsune-tail.png" width="64" height="16"/>
 <tile id="0">
  <objectgroup draworder="index" id="2">
   <object id="2" x="4" y="4" width="8" height="8">
    <properties>
     <property name="collidable" type="bool" value="true"/>
    </properties>
    <ellipse/>
   </object>
  </objectgroup>
  <animation>
   <frame tileid="0" duration="100"/>
   <frame tileid="1" duration="100"/>
   <frame tileid="2" duration="100"/>
   <frame tileid="3" duration="100"/>
  </animation>
 </tile>
 <tile id="1">
  <objectgroup>
   <object id="1" x="0" y="8">
    <properties>
     <property name="collidable" type="bool" value="true"/>
    </properties>
    <polyline points="0,0 12,0"/>
   </object>
  </objectgroup>
 </tile>
 <tile id="2">
  <objectgroup>
   <object id="1" x="0" y="8">
    <properties>
     <property name="collidable" type="bool" value="true"/>
    </properties>
    <polyline points="0,0 12,0"/>
   </object>
  </objectgroup>
 </tile>
 <tile id="3">
  <objectgroup>
   <object id="1" x="0" y="8">
    <properties>
     <property name="collidable" type="bool" value="true"/>
    </properties>
    <polyline points="0,0 12,0"/>
   </object>
  </objectgroup>
 </tile>
</tileset>
