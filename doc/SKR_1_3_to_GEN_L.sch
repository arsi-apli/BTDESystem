<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="7.2.0">
<drawing>
<settings>
<setting alwaysvectorfont="yes"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="no" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="2" name="Route2" color="1" fill="3" visible="no" active="no"/>
<layer number="3" name="Route3" color="4" fill="3" visible="no" active="no"/>
<layer number="4" name="Route4" color="1" fill="4" visible="no" active="no"/>
<layer number="5" name="Route5" color="4" fill="4" visible="no" active="no"/>
<layer number="6" name="Route6" color="1" fill="8" visible="no" active="no"/>
<layer number="7" name="Route7" color="4" fill="8" visible="no" active="no"/>
<layer number="8" name="Route8" color="1" fill="2" visible="no" active="no"/>
<layer number="9" name="Route9" color="4" fill="2" visible="no" active="no"/>
<layer number="10" name="Route10" color="1" fill="7" visible="no" active="no"/>
<layer number="11" name="Route11" color="4" fill="7" visible="no" active="no"/>
<layer number="12" name="Route12" color="1" fill="5" visible="no" active="no"/>
<layer number="13" name="Route13" color="4" fill="5" visible="no" active="no"/>
<layer number="14" name="Route14" color="1" fill="6" visible="no" active="no"/>
<layer number="15" name="Route15" color="4" fill="6" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="15" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="53" name="tGND_GNDA" color="7" fill="9" visible="no" active="no"/>
<layer number="54" name="bGND_GNDA" color="1" fill="9" visible="no" active="no"/>
<layer number="90" name="Modules" color="5" fill="1" visible="yes" active="yes"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
<layer number="99" name="SpiceOrder" color="5" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="con-panduit">
<packages>
<package name="057-010-0">
<description>&lt;b&gt;CONNECTOR&lt;/b&gt;&lt;p&gt;
series 057 contact pc board low profile headers&lt;p&gt;
angled</description>
<wire x1="-1.9" y1="-0.23" x2="-1.9" y2="5.86" width="0.2032" layer="21"/>
<wire x1="-1.9" y1="-0.23" x2="1.9" y2="-0.23" width="0.2032" layer="21"/>
<wire x1="1.9" y1="-0.23" x2="1.9" y2="5.86" width="0.2032" layer="21"/>
<wire x1="-5.8" y1="5.22" x2="-5.1" y2="3.25" width="0.4064" layer="21"/>
<wire x1="-5.1" y1="3.25" x2="-4.4" y2="5.22" width="0.4064" layer="21"/>
<wire x1="-4.4" y1="5.22" x2="-5.8" y2="5.22" width="0.4064" layer="21"/>
<wire x1="-10.21" y1="-2.54" x2="-10.21" y2="5.86" width="0.2032" layer="21"/>
<wire x1="10.21" y1="5.86" x2="10.21" y2="-2.44" width="0.2032" layer="21"/>
<wire x1="-10.16" y1="-2.54" x2="-7.62" y2="-2.54" width="0.2032" layer="21"/>
<wire x1="-7.62" y1="-2.54" x2="-7.62" y2="-5.98" width="0.2032" layer="21"/>
<wire x1="10.16" y1="-2.54" x2="7.62" y2="-2.54" width="0.2032" layer="21"/>
<wire x1="7.62" y1="-2.54" x2="7.62" y2="-6.05" width="0.2032" layer="21"/>
<wire x1="7.61" y1="-6.04" x2="-7.61" y2="-6.04" width="0.2032" layer="21"/>
<wire x1="-10.21" y1="5.86" x2="10.21" y2="5.86" width="0.2032" layer="21"/>
<pad name="1" x="-5.08" y="-5.08" drill="1" shape="octagon"/>
<pad name="2" x="-5.08" y="-2.54" drill="1" shape="octagon"/>
<pad name="3" x="-2.54" y="-5.08" drill="1" shape="octagon"/>
<pad name="4" x="-2.54" y="-2.54" drill="1" shape="octagon"/>
<pad name="5" x="0" y="-5.08" drill="1" shape="octagon"/>
<pad name="6" x="0" y="-2.54" drill="1" shape="octagon"/>
<pad name="7" x="2.54" y="-5.08" drill="1" shape="octagon"/>
<pad name="8" x="2.54" y="-2.54" drill="1" shape="octagon"/>
<pad name="9" x="5.08" y="-5.08" drill="1" shape="octagon"/>
<pad name="10" x="5.08" y="-2.54" drill="1" shape="octagon"/>
<text x="-6.35" y="-8.89" size="1.778" layer="25">&gt;NAME</text>
<text x="-8.89" y="6.35" size="1.778" layer="27">&gt;VALUE</text>
<hole x="-13.48" y="3.66" drill="2.8"/>
<hole x="13.73" y="3.66" drill="2.8"/>
</package>
<package name="057-010-1">
<description>&lt;b&gt;CONNECTOR&lt;/b&gt;&lt;p&gt;
series 057 contact pc board low profile headers&lt;p&gt;
straight</description>
<wire x1="-1.9" y1="-3.32" x2="-1.9" y2="-4.03" width="0.2032" layer="21"/>
<wire x1="1.9" y1="-3.32" x2="1.9" y2="-4.03" width="0.2032" layer="21"/>
<wire x1="-7.5" y1="-1.97" x2="-6.8" y2="-3.04" width="0.4064" layer="21"/>
<wire x1="-6.8" y1="-3.04" x2="-6.1" y2="-1.97" width="0.4064" layer="21"/>
<wire x1="-6.1" y1="-1.97" x2="-7.5" y2="-1.97" width="0.4064" layer="21"/>
<wire x1="-10.21" y1="-4.1" x2="-10.21" y2="4.1" width="0.2032" layer="21"/>
<wire x1="-10.21" y1="-4.1" x2="10.21" y2="-4.1" width="0.2032" layer="21"/>
<wire x1="10.21" y1="-4.1" x2="10.21" y2="4.1" width="0.2032" layer="21"/>
<wire x1="10.21" y1="4.1" x2="-10.21" y2="4.1" width="0.2032" layer="21"/>
<wire x1="-9.41" y1="-3.3" x2="-9.41" y2="3.3" width="0.2032" layer="21"/>
<wire x1="-9.41" y1="3.3" x2="9.41" y2="3.3" width="0.2032" layer="21"/>
<wire x1="9.41" y1="3.3" x2="9.41" y2="-3.3" width="0.2032" layer="21"/>
<wire x1="9.41" y1="-3.3" x2="1.9" y2="-3.3" width="0.2032" layer="21"/>
<wire x1="-1.9" y1="-3.3" x2="-9.41" y2="-3.3" width="0.2032" layer="21"/>
<wire x1="-10.21" y1="4.1" x2="-9.41" y2="3.3" width="0.2032" layer="21"/>
<wire x1="-10.21" y1="-4.1" x2="-9.41" y2="-3.3" width="0.2032" layer="21"/>
<wire x1="10.21" y1="4.1" x2="9.41" y2="3.3" width="0.2032" layer="21"/>
<wire x1="9.41" y1="-3.3" x2="10.21" y2="-4.1" width="0.2032" layer="21"/>
<pad name="1" x="-5.08" y="-1.27" drill="1" shape="square"/>
<pad name="2" x="-5.08" y="1.27" drill="1" shape="square"/>
<pad name="3" x="-2.54" y="-1.27" drill="1" shape="square"/>
<pad name="4" x="-2.54" y="1.27" drill="1" shape="square"/>
<pad name="5" x="0" y="-1.27" drill="1" shape="square"/>
<pad name="6" x="0" y="1.27" drill="1" shape="square"/>
<pad name="7" x="2.54" y="-1.27" drill="1" shape="square"/>
<pad name="8" x="2.54" y="1.27" drill="1" shape="square"/>
<pad name="9" x="5.08" y="-1.27" drill="1" shape="square"/>
<pad name="10" x="5.08" y="1.27" drill="1" shape="square"/>
<text x="-6.33" y="-6.88" size="1.778" layer="25">&gt;NAME</text>
<text x="-8.35" y="4.55" size="1.778" layer="27">&gt;VALUE</text>
</package>
</packages>
<symbols>
<symbol name="MV">
<wire x1="0" y1="0" x2="-1.27" y2="0" width="0.6096" layer="94"/>
<wire x1="-2.54" y1="0" x2="-1.27" y2="0" width="0.1524" layer="94"/>
<text x="1.016" y="-0.762" size="1.524" layer="95">&gt;NAME</text>
<text x="-2.54" y="1.905" size="1.778" layer="96">&gt;VALUE</text>
<pin name="S" x="-5.08" y="0" visible="off" length="short" direction="pas"/>
</symbol>
<symbol name="M">
<wire x1="0" y1="0" x2="-1.27" y2="0" width="0.6096" layer="94"/>
<wire x1="-2.54" y1="0" x2="-1.27" y2="0" width="0.1524" layer="94"/>
<text x="1.016" y="-0.762" size="1.524" layer="95">&gt;NAME</text>
<pin name="S" x="-5.08" y="0" visible="off" length="short" direction="pas"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="057-010-" prefix="X">
<description>&lt;b&gt;CONNECTOR&lt;/b&gt;&lt;p&gt;
10-pin series 057 contact pc board low profile headers</description>
<gates>
<gate name="-1" symbol="MV" x="-10.16" y="43.18" addlevel="always" swaplevel="1"/>
<gate name="-2" symbol="M" x="12.7" y="43.18" addlevel="always" swaplevel="1"/>
<gate name="-3" symbol="M" x="-10.16" y="38.1" addlevel="always" swaplevel="1"/>
<gate name="-4" symbol="M" x="12.7" y="38.1" addlevel="always" swaplevel="1"/>
<gate name="-5" symbol="M" x="-10.16" y="33.02" addlevel="always" swaplevel="1"/>
<gate name="-6" symbol="M" x="12.7" y="33.02" addlevel="always" swaplevel="1"/>
<gate name="-7" symbol="M" x="-10.16" y="27.94" addlevel="always" swaplevel="1"/>
<gate name="-8" symbol="M" x="12.7" y="27.94" addlevel="always" swaplevel="1"/>
<gate name="-9" symbol="M" x="-10.16" y="22.86" addlevel="always" swaplevel="1"/>
<gate name="-10" symbol="M" x="12.7" y="22.86" addlevel="always" swaplevel="1"/>
</gates>
<devices>
<device name="0" package="057-010-0">
<connects>
<connect gate="-1" pin="S" pad="1"/>
<connect gate="-10" pin="S" pad="10"/>
<connect gate="-2" pin="S" pad="2"/>
<connect gate="-3" pin="S" pad="3"/>
<connect gate="-4" pin="S" pad="4"/>
<connect gate="-5" pin="S" pad="5"/>
<connect gate="-6" pin="S" pad="6"/>
<connect gate="-7" pin="S" pad="7"/>
<connect gate="-8" pin="S" pad="8"/>
<connect gate="-9" pin="S" pad="9"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
<device name="1" package="057-010-1">
<connects>
<connect gate="-1" pin="S" pad="1"/>
<connect gate="-10" pin="S" pad="10"/>
<connect gate="-2" pin="S" pad="2"/>
<connect gate="-3" pin="S" pad="3"/>
<connect gate="-4" pin="S" pad="4"/>
<connect gate="-5" pin="S" pad="5"/>
<connect gate="-6" pin="S" pad="6"/>
<connect gate="-7" pin="S" pad="7"/>
<connect gate="-8" pin="S" pad="8"/>
<connect gate="-9" pin="S" pad="9"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="" constant="no"/>
<attribute name="MPN" value="" constant="no"/>
<attribute name="OC_FARNELL" value="unknown" constant="no"/>
<attribute name="OC_NEWARK" value="unknown" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="supply1">
<packages>
</packages>
<symbols>
<symbol name="GND">
<wire x1="-1.905" y1="0" x2="1.905" y2="0" width="0.254" layer="94"/>
<text x="-2.54" y="-2.54" size="1.778" layer="96">&gt;VALUE</text>
<pin name="GND" x="0" y="2.54" visible="off" length="short" direction="sup" rot="R270"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="GND" prefix="GND">
<description>&lt;b&gt;SUPPLY SYMBOL&lt;/b&gt;</description>
<gates>
<gate name="1" symbol="GND" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
</class>
</classes>
<parts>
<part name="EXP2" library="con-panduit" deviceset="057-010-" device="1" value="SKR 1.3"/>
<part name="AUX1" library="con-panduit" deviceset="057-010-" device="1" value="GEN_L"/>
<part name="GND1" library="supply1" deviceset="GND" device=""/>
</parts>
<sheets>
<sheet>
<plain>
</plain>
<instances>
<instance part="EXP2" gate="-1" x="7.62" y="55.88"/>
<instance part="EXP2" gate="-2" x="30.48" y="55.88" rot="MR0"/>
<instance part="EXP2" gate="-3" x="7.62" y="50.8"/>
<instance part="EXP2" gate="-4" x="30.48" y="50.8" rot="MR0"/>
<instance part="EXP2" gate="-5" x="7.62" y="45.72"/>
<instance part="EXP2" gate="-6" x="30.48" y="45.72" rot="MR0"/>
<instance part="EXP2" gate="-7" x="7.62" y="40.64"/>
<instance part="EXP2" gate="-8" x="30.48" y="40.64" rot="MR0"/>
<instance part="EXP2" gate="-9" x="7.62" y="35.56"/>
<instance part="EXP2" gate="-10" x="30.48" y="35.56" rot="MR0"/>
<instance part="AUX1" gate="-1" x="106.68" y="55.88"/>
<instance part="AUX1" gate="-2" x="129.54" y="55.88" rot="MR0"/>
<instance part="AUX1" gate="-3" x="106.68" y="50.8"/>
<instance part="AUX1" gate="-4" x="129.54" y="50.8" rot="MR0"/>
<instance part="AUX1" gate="-5" x="106.68" y="45.72"/>
<instance part="AUX1" gate="-6" x="129.54" y="45.72" rot="MR0"/>
<instance part="AUX1" gate="-7" x="106.68" y="40.64"/>
<instance part="AUX1" gate="-8" x="129.54" y="40.64" rot="MR0"/>
<instance part="GND1" gate="1" x="96.52" y="48.26"/>
</instances>
<busses>
</busses>
<nets>
<net name="GND" class="0">
<segment>
<pinref part="AUX1" gate="-3" pin="S"/>
<wire x1="101.6" y1="50.8" x2="96.52" y2="50.8" width="0.1524" layer="91"/>
<label x="91.44" y="50.8" size="1.778" layer="95" rot="R180"/>
<pinref part="GND1" gate="1" pin="GND"/>
<wire x1="96.52" y1="50.8" x2="91.44" y2="50.8" width="0.1524" layer="91"/>
<junction x="96.52" y="50.8"/>
</segment>
<segment>
<pinref part="AUX1" gate="-4" pin="S"/>
<wire x1="134.62" y1="50.8" x2="137.16" y2="50.8" width="0.1524" layer="91"/>
<label x="152.4" y="50.8" size="1.778" layer="95"/>
<wire x1="137.16" y1="50.8" x2="142.24" y2="50.8" width="0.1524" layer="91"/>
<wire x1="142.24" y1="50.8" x2="149.86" y2="50.8" width="0.1524" layer="91"/>
<wire x1="142.24" y1="50.8" x2="142.24" y2="30.48" width="0.1524" layer="91"/>
<pinref part="EXP2" gate="-2" pin="S"/>
<wire x1="50.8" y1="55.88" x2="35.56" y2="55.88" width="0.1524" layer="91"/>
<wire x1="142.24" y1="30.48" x2="50.8" y2="30.48" width="0.1524" layer="91"/>
<wire x1="50.8" y1="30.48" x2="50.8" y2="55.88" width="0.1524" layer="91"/>
<junction x="142.24" y="50.8"/>
<label x="40.64" y="55.88" size="1.778" layer="95"/>
</segment>
</net>
<net name="TXD" class="0">
<segment>
<pinref part="EXP2" gate="-9" pin="S"/>
<wire x1="2.54" y1="35.56" x2="-2.54" y2="35.56" width="0.1524" layer="91"/>
<label x="-27.94" y="35.56" size="1.778" layer="95" xref="yes"/>
<wire x1="-2.54" y1="35.56" x2="-20.32" y2="35.56" width="0.1524" layer="91"/>
<wire x1="-2.54" y1="35.56" x2="-2.54" y2="27.94" width="0.1524" layer="91"/>
<pinref part="AUX1" gate="-8" pin="S"/>
<wire x1="134.62" y1="40.64" x2="144.78" y2="40.64" width="0.1524" layer="91"/>
<wire x1="144.78" y1="40.64" x2="149.86" y2="40.64" width="0.1524" layer="91"/>
<wire x1="-2.54" y1="27.94" x2="144.78" y2="27.94" width="0.1524" layer="91"/>
<wire x1="144.78" y1="27.94" x2="144.78" y2="40.64" width="0.1524" layer="91"/>
<junction x="-2.54" y="35.56"/>
<junction x="144.78" y="40.64"/>
<label x="157.48" y="40.64" size="1.778" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="RXD" class="0">
<segment>
<pinref part="EXP2" gate="-7" pin="S"/>
<wire x1="2.54" y1="40.64" x2="-10.16" y2="40.64" width="0.1524" layer="91"/>
<label x="-20.32" y="40.64" size="1.778" layer="95" rot="R180" xref="yes"/>
<wire x1="-10.16" y1="40.64" x2="-20.32" y2="40.64" width="0.1524" layer="91"/>
<wire x1="-10.16" y1="40.64" x2="-10.16" y2="22.86" width="0.1524" layer="91"/>
<pinref part="AUX1" gate="-6" pin="S"/>
<wire x1="134.62" y1="45.72" x2="147.32" y2="45.72" width="0.1524" layer="91"/>
<wire x1="147.32" y1="45.72" x2="149.86" y2="45.72" width="0.1524" layer="91"/>
<wire x1="-10.16" y1="22.86" x2="147.32" y2="22.86" width="0.1524" layer="91"/>
<wire x1="147.32" y1="22.86" x2="147.32" y2="45.72" width="0.1524" layer="91"/>
<junction x="-10.16" y="40.64"/>
<junction x="147.32" y="45.72"/>
<label x="149.86" y="45.72" size="1.778" layer="95" xref="yes"/>
</segment>
</net>
<net name="NC" class="0">
<segment>
<pinref part="EXP2" gate="-1" pin="S"/>
<wire x1="2.54" y1="55.88" x2="-5.08" y2="55.88" width="0.1524" layer="91"/>
<label x="-5.08" y="55.88" size="1.778" layer="95" rot="R180"/>
</segment>
<segment>
<pinref part="AUX1" gate="-5" pin="S"/>
<wire x1="101.6" y1="45.72" x2="91.44" y2="45.72" width="0.1524" layer="91"/>
<label x="91.44" y="45.72" size="1.778" layer="95" rot="R180"/>
</segment>
<segment>
<pinref part="AUX1" gate="-7" pin="S"/>
<wire x1="101.6" y1="40.64" x2="91.44" y2="40.64" width="0.1524" layer="91"/>
<label x="91.44" y="40.64" size="1.778" layer="95" rot="R180"/>
</segment>
</net>
<net name="RESET" class="0">
<segment>
<pinref part="EXP2" gate="-3" pin="S"/>
<wire x1="2.54" y1="50.8" x2="-5.08" y2="50.8" width="0.1524" layer="91"/>
<label x="-5.08" y="50.8" size="1.778" layer="95" rot="R180"/>
</segment>
</net>
<net name="0.18" class="0">
<segment>
<pinref part="EXP2" gate="-5" pin="S"/>
<wire x1="2.54" y1="45.72" x2="-5.08" y2="45.72" width="0.1524" layer="91"/>
<label x="-5.08" y="45.72" size="1.778" layer="95" rot="R180"/>
</segment>
</net>
<net name="1.31" class="0">
<segment>
<pinref part="EXP2" gate="-4" pin="S"/>
<wire x1="35.56" y1="50.8" x2="40.64" y2="50.8" width="0.1524" layer="91"/>
<label x="40.64" y="50.8" size="1.778" layer="95"/>
</segment>
</net>
<net name="3.25" class="0">
<segment>
<pinref part="EXP2" gate="-6" pin="S"/>
<wire x1="35.56" y1="45.72" x2="40.64" y2="45.72" width="0.1524" layer="91"/>
<label x="40.64" y="45.72" size="1.778" layer="95"/>
</segment>
</net>
<net name="3.26" class="0">
<segment>
<pinref part="EXP2" gate="-8" pin="S"/>
<wire x1="35.56" y1="40.64" x2="40.64" y2="40.64" width="0.1524" layer="91"/>
<label x="40.64" y="40.64" size="1.778" layer="95"/>
</segment>
</net>
<net name="0.17" class="0">
<segment>
<pinref part="EXP2" gate="-10" pin="S"/>
<wire x1="35.56" y1="35.56" x2="40.64" y2="35.56" width="0.1524" layer="91"/>
<label x="40.64" y="35.56" size="1.778" layer="95"/>
</segment>
</net>
<net name="+5V" class="0">
<segment>
<pinref part="AUX1" gate="-1" pin="S"/>
<wire x1="101.6" y1="55.88" x2="91.44" y2="55.88" width="0.1524" layer="91"/>
<label x="91.44" y="55.88" size="1.778" layer="95" rot="R180"/>
</segment>
<segment>
<pinref part="AUX1" gate="-2" pin="S"/>
<wire x1="134.62" y1="55.88" x2="149.86" y2="55.88" width="0.1524" layer="91"/>
<label x="152.4" y="55.88" size="1.778" layer="95"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
</schematic>
</drawing>
</eagle>
