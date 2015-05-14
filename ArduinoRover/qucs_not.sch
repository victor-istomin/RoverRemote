<Qucs Schematic 0.0.18>
<Properties>
  <View=0,0,1240,800,1,0,0>
  <Grid=10,10,1>
  <DataSet=test.dat>
  <DataDisplay=test.dpl>
  <OpenDisplay=1>
  <Script=test.m>
  <RunScript=0>
  <showFrame=0>
  <FrameText0=Название>
  <FrameText1=Чертил:>
  <FrameText2=Дата:>
  <FrameText3=Версия:>
</Properties>
<Symbol>
  <.PortSym 40 20 1 0>
  <.PortSym 50 50 2 0>
  <.PortSym 70 80 3 0>
  <.PortSym 70 120 4 0>
  <.PortSym 70 160 5 0>
  <.PortSym 70 200 6 0>
</Symbol>
<Components>
  <IProbe Amp1 1 230 460 -26 16 1 2>
  <_BJT S8050 1 290 350 8 -26 0 0 "npn" 0 "6.734f" 0 "1" 0 "1" 0 "61.27m" 0 "0" 0 "74.03" 0 "0" 0 "6.734f" 0 "1.216" 0 "0" 0 "2" 0 "335.3" 0 "0.7925" 0 "0" 0 "0" 0 "1" 0 "0" 0 "10" 0 "4.493p" 0 "0.75" 0 "0.2593" 0 "3.638p" 0 "0.75" 0 "0.3085" 0 "1" 0 "0" 0 "0.75" 0 "0" 0 "0.5" 0 "300.8p" 0 "2" 0 "4" 0 "0.4" 0 "243.1n" 0 "26.85" 0 "0" 0 "1" 0 "1" 0 "0" 0 "1" 0 "1" 0 "0" 0 "1.5" 0 "3" 0 "1.11" 0 "26.85" 0 "1" 0>
  <_BJT S8050_2 1 660 350 8 -26 0 0 "npn" 0 "6.734f" 0 "1" 0 "1" 0 "61.27m" 0 "0" 0 "74.03" 0 "0" 0 "6.734f" 0 "1.216" 0 "0" 0 "2" 0 "335.3" 0 "0.7925" 0 "0" 0 "0" 0 "1" 0 "0" 0 "10" 0 "4.493p" 0 "0.75" 0 "0.2593" 0 "3.638p" 0 "0.75" 0 "0.3085" 0 "1" 0 "0" 0 "0.75" 0 "0" 0 "0.5" 0 "300.8p" 0 "2" 0 "4" 0 "0.4" 0 "243.1n" 0 "26.85" 0 "0" 0 "1" 0 "1" 0 "0" 0 "1" 0 "1" 0 "0" 0 "1.5" 0 "3" 0 "1.11" 0 "26.85" 0 "1" 0>
  <R R1 1 230 350 -26 15 0 0 "5600 Ohm" 1 "26.85" 0 "0.0" 0 "0.0" 0 "26.85" 0 "european" 0>
  <R R5 1 600 350 -26 15 0 0 "5600 Ohm" 1 "26.85" 0 "0.0" 0 "0.0" 0 "26.85" 0 "european" 0>
  <R R2 1 360 220 15 -26 1 3 "1000 Ohm" 1 "26.85" 0 "0.0" 0 "0.0" 0 "26.85" 0 "european" 0>
  <R R4 1 660 220 15 -26 1 3 "1000 Ohm" 1 "26.85" 0 "0.0" 0 "0.0" 0 "26.85" 0 "european" 0>
  <Port P3 1 410 300 4 12 1 2 "3" 0 "out" 0>
  <R Rload 1 410 430 15 -26 0 1 "8000 Ohm" 0 "26.85" 0 "0.0" 0 "0.0" 0 "26.85" 0 "european" 0>
  <VProbe Vol1 1 510 350 -16 28 0 3>
  <Port P2 1 570 260 -28 -23 0 3 "2" 0 "in" 0>
  <Port P1 1 200 260 -28 -23 0 3 "1" 0 "in" 0>
  <VProbe IN1 1 160 540 28 -16 1 0>
  <VProbe IN2 1 580 540 28 -16 1 0>
  <.DC DC1 1 520 620 0 63 0 0 "26.85" 0 "0.001" 0 "1 pA" 0 "1 uV" 0 "no" 0 "5000" 0 "no" 0 "none" 0 "HouseholderQR" 0>
  <Vdc V1 1 80 320 18 -26 0 1 "5 V" 1>
  <Port P5 5 80 290 -23 12 0 0 "5" 0 "analog" 0>
  <Port P6 5 80 350 -23 12 0 0 "6" 0 "analog" 0>
  <VProbe Vol2 1 860 350 -16 28 0 3>
  <Port P4 1 750 300 4 12 1 2 "4" 0 "out" 0>
  <R Rload2 1 750 430 15 -26 0 1 "8000 Ohm" 0 "26.85" 0 "0.0" 0 "0.0" 0 "26.85" 0 "european" 0>
</Components>
<Wires>
  <290 320 360 320 "" 0 0 0 "">
  <290 380 360 380 "" 0 0 0 "">
  <360 280 410 280 "" 0 0 0 "">
  <260 460 360 460 "" 0 0 0 "">
  <410 280 410 300 "" 0 0 0 "">
  <360 250 360 280 "" 0 0 0 "">
  <360 180 360 190 "" 0 0 0 "">
  <410 460 470 460 "" 0 0 0 "">
  <360 460 410 460 "" 0 0 0 "">
  <360 380 360 460 "" 0 0 0 "">
  <360 280 360 320 "" 0 0 0 "">
  <660 250 660 280 "" 0 0 0 "">
  <660 380 660 460 "" 0 0 0 "">
  <660 280 660 320 "" 0 0 0 "">
  <570 260 570 350 "" 0 0 0 "">
  <660 180 660 190 "" 0 0 0 "">
  <360 180 600 180 "" 0 0 0 "">
  <410 300 410 400 "" 0 0 0 "">
  <410 280 470 280 "" 0 0 0 "">
  <470 280 470 340 "" 0 0 0 "">
  <470 340 490 340 "" 0 0 0 "">
  <470 460 590 460 "" 0 0 0 "">
  <470 360 470 460 "" 0 0 0 "">
  <470 360 490 360 "" 0 0 0 "">
  <200 260 200 350 "" 0 0 0 "">
  <590 460 660 460 "" 0 0 0 "">
  <150 350 200 350 "" 0 0 0 "">
  <150 350 150 520 "" 0 0 0 "">
  <590 460 590 520 "" 0 0 0 "">
  <570 350 570 520 "" 0 0 0 "">
  <170 460 200 460 "" 0 0 0 "">
  <170 460 170 520 "" 0 0 0 "">
  <80 460 170 460 "" 0 0 0 "">
  <80 180 220 180 "" 0 0 0 "">
  <80 180 80 290 "" 0 0 0 "">
  <80 350 80 460 "" 0 0 0 "">
  <660 280 750 280 "" 0 0 0 "">
  <660 460 750 460 "" 0 0 0 "">
  <750 280 750 300 "" 0 0 0 "">
  <750 460 830 460 "" 0 0 0 "">
  <750 280 830 280 "" 0 0 0 "">
  <830 280 830 340 "" 0 0 0 "">
  <830 340 840 340 "" 0 0 0 "">
  <830 360 830 460 "" 0 0 0 "">
  <830 360 840 360 "" 0 0 0 "">
  <750 300 750 400 "" 0 0 0 "">
  <200 260 220 260 "" 0 0 0 "">
  <220 180 360 180 "" 0 0 0 "">
  <220 180 220 260 "" 0 0 0 "">
  <570 260 600 260 "" 0 0 0 "">
  <600 180 660 180 "" 0 0 0 "">
  <600 180 600 260 "" 0 0 0 "">
</Wires>
<Diagrams>
  <Tab 79 679 412 70 3 #c0c0c0 1 00 1 0 1 1 1 0 1 1 1 0 1 1 315 0 225 "" "" "">
	<"IN1.V" #0000ff 0 3 0 0 0>
	<"Vol1.V" #0000ff 0 3 0 0 0>
	<"IN2.V" #0000ff 0 3 0 0 0>
	<"Vol2.V" #0000ff 0 3 0 0 0>
	<"Amp1.I" #0000ff 0 3 0 0 0>
  </Tab>
</Diagrams>
<Paintings>
</Paintings>