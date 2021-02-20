EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "TruePosition GPSDO control"
Date ""
Rev "A"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Regulator_Linear:L7805 U1
U 1 1 5E7E42AC
P 5500 2000
F 0 "U1" H 5500 2242 50  0000 C CNN
F 1 "L7805" H 5500 2151 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 5525 1850 50  0001 L CIN
F 3 "http://www.st.com/content/ccc/resource/technical/document/datasheet/41/4f/b3/b0/12/d4/47/88/CD00000444.pdf/files/CD00000444.pdf/jcr:content/translations/en.CD00000444.pdf" H 5500 1950 50  0001 C CNN
	1    5500 2000
	1    0    0    -1  
$EndComp
$Comp
L Device:C C3
U 1 1 5E7E89D9
P 5000 2150
F 0 "C3" H 4950 1900 50  0000 L CNN
F 1 "100n" H 4900 1800 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D5.0mm_W2.5mm_P2.50mm" H 5038 2000 50  0001 C CNN
F 3 "~" H 5000 2150 50  0001 C CNN
	1    5000 2150
	1    0    0    -1  
$EndComp
$Comp
L Device:C C6
U 1 1 5E7E9418
P 6000 3000
F 0 "C6" H 5950 2750 50  0000 L CNN
F 1 "100n" H 5950 2650 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D5.0mm_W2.5mm_P2.50mm" H 6038 2850 50  0001 C CNN
F 3 "~" H 6000 3000 50  0001 C CNN
	1    6000 3000
	1    0    0    -1  
$EndComp
$Comp
L Device:C C5
U 1 1 5E7E9A56
P 6000 2150
F 0 "C5" H 5950 1900 50  0000 L CNN
F 1 "100n" H 5900 1800 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D5.0mm_W2.5mm_P2.50mm" H 6038 2000 50  0001 C CNN
F 3 "~" H 6000 2150 50  0001 C CNN
	1    6000 2150
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C2
U 1 1 5E7E9D9F
P 4450 2150
F 0 "C2" H 4400 2600 50  0000 L CNN
F 1 "2200uF/35V" H 4350 2500 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D16.0mm_P7.50mm" H 4488 2000 50  0001 C CNN
F 3 "~" H 4450 2150 50  0001 C CNN
	1    4450 2150
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C7
U 1 1 5E7EA8E3
P 6300 2150
F 0 "C7" H 6250 1950 50  0000 L CNN
F 1 "4,7uF/25V" H 6250 1850 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.00mm" H 6338 2000 50  0001 C CNN
F 3 "~" H 6300 2150 50  0001 C CNN
	1    6300 2150
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C8
U 1 1 5E7EB9AE
P 6300 3000
F 0 "C8" H 6250 2750 50  0000 L CNN
F 1 "4.7uF/25V" H 6250 2650 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D5.0mm_P2.00mm" H 6338 2850 50  0001 C CNN
F 3 "~" H 6300 3000 50  0001 C CNN
	1    6300 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	4450 2000 4750 2000
Connection ~ 5000 2000
Wire Wire Line
	5000 2000 5200 2000
$Comp
L Device:C C4
U 1 1 5E82948E
P 5000 3000
F 0 "C4" H 4950 2750 50  0000 L CNN
F 1 "100n" H 4950 2650 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D5.0mm_W2.5mm_P2.50mm" H 5038 2850 50  0001 C CNN
F 3 "~" H 5000 3000 50  0001 C CNN
	1    5000 3000
	1    0    0    -1  
$EndComp
Wire Wire Line
	5200 2850 5000 2850
Wire Wire Line
	4750 2850 4750 2000
Connection ~ 5000 2850
Wire Wire Line
	5000 2850 4750 2850
Connection ~ 4750 2000
Wire Wire Line
	4750 2000 5000 2000
Wire Wire Line
	5800 2000 6000 2000
Connection ~ 6000 2000
Wire Wire Line
	6000 2000 6300 2000
Wire Wire Line
	5800 2850 6000 2850
Connection ~ 6000 2850
Wire Wire Line
	6000 2850 6300 2850
Connection ~ 6300 2000
Connection ~ 6300 2850
Wire Wire Line
	4450 2300 5000 2300
Connection ~ 5000 2300
Wire Wire Line
	5000 2300 5500 2300
Connection ~ 5500 2300
Wire Wire Line
	5500 2300 6000 2300
Connection ~ 6000 2300
Wire Wire Line
	6000 2300 6300 2300
Connection ~ 6000 3150
Wire Wire Line
	6300 3150 6000 3150
Wire Wire Line
	5000 3150 4450 3150
Connection ~ 5000 3150
Connection ~ 4450 2300
Connection ~ 4450 3150
$Comp
L power:GND #PWR07
U 1 1 5E8359EF
P 4450 3150
F 0 "#PWR07" H 4450 2900 50  0001 C CNN
F 1 "GND" H 4455 2977 50  0000 C CNN
F 2 "" H 4450 3150 50  0001 C CNN
F 3 "" H 4450 3150 50  0001 C CNN
	1    4450 3150
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR010
U 1 1 5E83605D
P 6300 2000
F 0 "#PWR010" H 6300 1850 50  0001 C CNN
F 1 "+5V" H 6315 2173 50  0000 C CNN
F 2 "" H 6300 2000 50  0001 C CNN
F 3 "" H 6300 2000 50  0001 C CNN
	1    6300 2000
	1    0    0    -1  
$EndComp
$Comp
L power:+10V #PWR011
U 1 1 5E836706
P 6300 2850
F 0 "#PWR011" H 6300 2700 50  0001 C CNN
F 1 "+10V" H 6315 3023 50  0000 C CNN
F 2 "" H 6300 2850 50  0001 C CNN
F 3 "" H 6300 2850 50  0001 C CNN
	1    6300 2850
	1    0    0    -1  
$EndComp
$Comp
L Regulator_Linear:LM7810_TO220 U2
U 1 1 5E836E30
P 5500 2850
F 0 "U2" H 5500 3092 50  0000 C CNN
F 1 "LM7810_TO220" H 5500 3001 50  0000 C CNN
F 2 "Package_TO_SOT_THT:TO-220-3_Vertical" H 5500 3075 50  0001 C CIN
F 3 "http://www.fairchildsemi.com/ds/LM/LM7805.pdf" H 5500 2800 50  0001 C CNN
	1    5500 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	5000 3150 5500 3150
Connection ~ 5500 3150
Wire Wire Line
	5500 3150 6000 3150
$Comp
L MyLib:BluePill_1 BP1
U 1 1 5E83AC76
P 4600 4000
F 0 "BP1" H 5175 4175 50  0000 C CNN
F 1 "BluePill_1" H 5175 4084 50  0000 C CNN
F 2 "Cutom-modules:STM32-BluePill" H 5850 2050 50  0001 C CNN
F 3 "" H 5850 2050 50  0001 C CNN
	1    4600 4000
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR06
U 1 1 5E83E250
P 4150 6100
F 0 "#PWR06" H 4150 5850 50  0001 C CNN
F 1 "GND" H 4155 5927 50  0000 C CNN
F 2 "" H 4150 6100 50  0001 C CNN
F 3 "" H 4150 6100 50  0001 C CNN
	1    4150 6100
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR08
U 1 1 5E83E6BB
P 6150 4050
F 0 "#PWR08" H 6150 3800 50  0001 C CNN
F 1 "GND" H 6155 3877 50  0000 C CNN
F 2 "" H 6150 4050 50  0001 C CNN
F 3 "" H 6150 4050 50  0001 C CNN
	1    6150 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	4400 5850 4150 5850
Wire Wire Line
	4150 5850 4150 6100
Wire Wire Line
	6150 4050 6050 4050
Wire Wire Line
	5950 4150 6050 4150
Wire Wire Line
	6050 4150 6050 4050
Connection ~ 6050 4050
Wire Wire Line
	6050 4050 5950 4050
$Comp
L power:+5V #PWR05
U 1 1 5E8415A0
P 4150 5750
F 0 "#PWR05" H 4150 5600 50  0001 C CNN
F 1 "+5V" H 4165 5923 50  0000 C CNN
F 2 "" H 4150 5750 50  0001 C CNN
F 3 "" H 4150 5750 50  0001 C CNN
	1    4150 5750
	1    0    0    -1  
$EndComp
Wire Wire Line
	4400 5750 4150 5750
$Comp
L power:GND #PWR09
U 1 1 5E85863E
P 6400 5600
F 0 "#PWR09" H 6400 5350 50  0001 C CNN
F 1 "GND" H 6405 5427 50  0000 C CNN
F 2 "" H 6400 5600 50  0001 C CNN
F 3 "" H 6400 5600 50  0001 C CNN
	1    6400 5600
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW1
U 1 1 5E84D043
P 4050 4000
F 0 "SW1" H 4050 4285 50  0000 C CNN
F 1 "SW_Mode" H 4050 4194 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 4050 4200 50  0001 C CNN
F 3 "~" H 4050 4200 50  0001 C CNN
	1    4050 4000
	-1   0    0    -1  
$EndComp
$Comp
L Switch:SW_Push SW2
U 1 1 5E84C9C6
P 4050 4350
F 0 "SW2" H 4050 4635 50  0000 C CNN
F 1 "SW_Sel" H 4050 4544 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 4050 4550 50  0001 C CNN
F 3 "~" H 4050 4550 50  0001 C CNN
	1    4050 4350
	-1   0    0    -1  
$EndComp
Wire Wire Line
	2300 5250 2150 5250
Wire Wire Line
	2300 4950 2150 4950
Wire Wire Line
	2150 4650 2300 4650
Wire Wire Line
	2600 5250 2700 5250
Wire Wire Line
	2700 4950 2600 4950
Wire Wire Line
	2700 4650 2600 4650
$Comp
L power:GND #PWR03
U 1 1 5E844B75
P 2750 6100
F 0 "#PWR03" H 2750 5850 50  0001 C CNN
F 1 "GND" H 2755 5927 50  0000 C CNN
F 2 "" H 2750 6100 50  0001 C CNN
F 3 "" H 2750 6100 50  0001 C CNN
	1    2750 6100
	-1   0    0    -1  
$EndComp
$Comp
L Device:LED D3
U 1 1 5E8447A6
P 2450 5250
F 0 "D3" H 2443 4995 50  0000 C CNN
F 1 "LED red" H 2443 5086 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 2450 5250 50  0001 C CNN
F 3 "~" H 2450 5250 50  0001 C CNN
	1    2450 5250
	1    0    0    1   
$EndComp
$Comp
L Device:LED D2
U 1 1 5E844296
P 2450 4950
F 0 "D2" H 2443 4695 50  0000 C CNN
F 1 "LED yellow" H 2443 4786 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 2450 4950 50  0001 C CNN
F 3 "~" H 2450 4950 50  0001 C CNN
	1    2450 4950
	1    0    0    1   
$EndComp
$Comp
L Device:LED D1
U 1 1 5E843C2F
P 2450 4650
F 0 "D1" H 2443 4395 50  0000 C CNN
F 1 "LED green" H 2443 4486 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 2450 4650 50  0001 C CNN
F 3 "~" H 2450 4650 50  0001 C CNN
	1    2450 4650
	1    0    0    1   
$EndComp
$Comp
L Device:R R3
U 1 1 5E8438BA
P 2850 5250
F 0 "R3" V 2643 5250 50  0000 C CNN
F 1 "1k5" V 2734 5250 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 2780 5250 50  0001 C CNN
F 3 "~" H 2850 5250 50  0001 C CNN
	1    2850 5250
	0    -1   1    0   
$EndComp
$Comp
L Device:R R2
U 1 1 5E8433CE
P 2850 4950
F 0 "R2" V 3057 4950 50  0000 C CNN
F 1 "1k5" V 2966 4950 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 2780 4950 50  0001 C CNN
F 3 "~" H 2850 4950 50  0001 C CNN
	1    2850 4950
	0    1    -1   0   
$EndComp
$Comp
L Device:R R1
U 1 1 5E842C41
P 2850 4650
F 0 "R1" V 2643 4650 50  0000 C CNN
F 1 "1k5" V 2734 4650 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 2780 4650 50  0001 C CNN
F 3 "~" H 2850 4650 50  0001 C CNN
	1    2850 4650
	0    -1   1    0   
$EndComp
$Comp
L Device:C C1
U 1 1 5E855AC8
P 4100 2150
F 0 "C1" H 4050 2600 50  0000 L CNN
F 1 "100nF" H 4000 2500 50  0000 L CNN
F 2 "Capacitor_THT:C_Disc_D5.0mm_W2.5mm_P2.50mm" H 4138 2000 50  0001 C CNN
F 3 "~" H 4100 2150 50  0001 C CNN
	1    4100 2150
	1    0    0    -1  
$EndComp
Wire Wire Line
	4250 4250 4250 4000
Wire Wire Line
	4400 5250 3500 5250
Wire Wire Line
	3500 5250 3500 4650
Wire Wire Line
	3500 4650 3000 4650
Wire Wire Line
	4400 5350 3350 5350
Wire Wire Line
	3350 5350 3350 4950
Wire Wire Line
	3350 4950 3000 4950
Wire Wire Line
	4400 5450 3150 5450
Wire Wire Line
	3150 5450 3150 5250
Wire Wire Line
	3150 5250 3000 5250
$Comp
L Device:R R4
U 1 1 5E89BCC6
P 3300 5900
F 0 "R4" V 3093 5900 50  0000 C CNN
F 1 "10k" V 3184 5900 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 3230 5900 50  0001 C CNN
F 3 "~" H 3300 5900 50  0001 C CNN
	1    3300 5900
	0    1    1    0   
$EndComp
Wire Wire Line
	4400 5550 3650 5550
Wire Wire Line
	3650 5900 3450 5900
Wire Wire Line
	3150 5900 3050 5900
Wire Wire Line
	2600 5650 2750 5650
Wire Wire Line
	2750 5650 2750 5700
Connection ~ 2150 4950
Wire Wire Line
	2150 4950 2150 4650
Wire Wire Line
	2150 5250 2150 4950
$Comp
L Connector_Generic:Conn_01x04 J3
U 1 1 5E8C0B0A
P 6700 5350
F 0 "J3" H 6650 5050 50  0000 L CNN
F 1 "GPSDO" H 6650 4950 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 6700 5350 50  0001 C CNN
F 3 "~" H 6700 5350 50  0001 C CNN
	1    6700 5350
	1    0    0    -1  
$EndComp
Wire Wire Line
	5950 5350 6300 5350
Wire Wire Line
	6300 5350 6300 5450
Wire Wire Line
	6300 5450 6500 5450
Wire Wire Line
	5950 5250 6500 5250
Wire Wire Line
	6500 5350 6400 5350
Wire Wire Line
	6400 5350 6400 5550
Wire Wire Line
	6400 5550 6500 5550
Connection ~ 6400 5550
Wire Wire Line
	6400 5550 6400 5600
$Comp
L Device:Transformer_1P_1S T1
U 1 1 5ED9B0D1
P 2550 2200
F 0 "T1" H 2550 2581 50  0000 C CNN
F 1 "230V/12V 16VA" H 2550 2490 50  0000 C CNN
F 2 "Cutom-modules:Transforme_Gerth_Bv_54112" H 2550 2200 50  0001 C CNN
F 3 "~" H 2550 2200 50  0001 C CNN
	1    2550 2200
	1    0    0    -1  
$EndComp
Wire Wire Line
	2950 2000 3050 2000
Wire Wire Line
	3050 2000 3050 1900
Wire Wire Line
	3050 1900 3500 1900
Wire Wire Line
	2950 2400 3050 2400
Wire Wire Line
	3050 2400 3050 2500
Wire Wire Line
	3050 2500 3500 2500
Wire Wire Line
	3800 2200 3800 2000
Wire Wire Line
	3800 2000 4100 2000
Connection ~ 4450 2000
Connection ~ 4100 2000
Wire Wire Line
	4100 2000 4450 2000
Wire Wire Line
	3200 2200 3200 3150
Wire Wire Line
	3200 3150 4100 3150
Wire Wire Line
	4100 2300 4450 2300
Wire Wire Line
	4100 2300 4100 3150
Connection ~ 4100 2300
Connection ~ 4100 3150
Wire Wire Line
	4100 3150 4450 3150
$Comp
L Connector_Generic:Conn_01x03 J2
U 1 1 5EDBF924
P 1500 2200
F 0 "J2" H 1418 2517 50  0000 C CNN
F 1 "Power 230V" H 1418 2426 50  0000 C CNN
F 2 "Connector_Wire:SolderWire-1.5sqmm_1x03_P6mm_D1.7mm_OD3mm" H 1500 2200 50  0001 C CNN
F 3 "~" H 1500 2200 50  0001 C CNN
	1    1500 2200
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1700 2100 2150 2100
Wire Wire Line
	2150 2100 2150 2000
Wire Wire Line
	1900 3150 3200 3150
Connection ~ 3200 3150
$Comp
L Device:R R5
U 1 1 5EDB2A36
P 2450 5650
F 0 "R5" V 2243 5650 50  0000 C CNN
F 1 "220" V 2334 5650 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 2380 5650 50  0001 C CNN
F 3 "~" H 2450 5650 50  0001 C CNN
	1    2450 5650
	0    1    1    0   
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 5EDD195E
P 7400 5400
F 0 "#PWR0101" H 7400 5150 50  0001 C CNN
F 1 "GND" H 7405 5227 50  0000 C CNN
F 2 "" H 7400 5400 50  0001 C CNN
F 3 "" H 7400 5400 50  0001 C CNN
	1    7400 5400
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR0102
U 1 1 5EDD2137
P 7300 3750
F 0 "#PWR0102" H 7300 3600 50  0001 C CNN
F 1 "+5V" H 7315 3923 50  0000 C CNN
F 2 "" H 7300 3750 50  0001 C CNN
F 3 "" H 7300 3750 50  0001 C CNN
	1    7300 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	2000 5650 2300 5650
Wire Wire Line
	5950 5150 6650 5150
Wire Wire Line
	6650 5150 6650 5050
Wire Wire Line
	5950 5050 6550 5050
Wire Wire Line
	6550 5050 6550 4950
Wire Wire Line
	2000 3650 2000 5650
Wire Wire Line
	3650 5900 3650 5550
Wire Wire Line
	4250 4250 4400 4250
Wire Wire Line
	4400 4350 4250 4350
Wire Wire Line
	3850 4000 3850 4350
Wire Wire Line
	2150 4400 2300 4400
Wire Wire Line
	2700 4400 2600 4400
$Comp
L Device:LED D4
U 1 1 5EE68135
P 2450 4400
F 0 "D4" H 2443 4145 50  0000 C CNN
F 1 "LED green" H 2443 4236 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 2450 4400 50  0001 C CNN
F 3 "~" H 2450 4400 50  0001 C CNN
	1    2450 4400
	1    0    0    1   
$EndComp
$Comp
L Device:R R6
U 1 1 5EE6813B
P 2850 4400
F 0 "R6" V 2643 4400 50  0000 C CNN
F 1 "1k5" V 2734 4400 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P10.16mm_Horizontal" V 2780 4400 50  0001 C CNN
F 3 "~" H 2850 4400 50  0001 C CNN
	1    2850 4400
	0    -1   1    0   
$EndComp
Wire Wire Line
	2150 4400 2150 4650
Connection ~ 2150 4650
$Comp
L power:+5V #PWR0103
U 1 1 5EE7246A
P 3050 4400
F 0 "#PWR0103" H 3050 4250 50  0001 C CNN
F 1 "+5V" H 3065 4573 50  0000 C CNN
F 2 "" H 3050 4400 50  0001 C CNN
F 3 "" H 3050 4400 50  0001 C CNN
	1    3050 4400
	1    0    0    -1  
$EndComp
Wire Wire Line
	2150 4400 2150 4000
Wire Wire Line
	2150 4000 3850 4000
Connection ~ 2150 4400
Connection ~ 3850 4000
$Comp
L power:GND #PWR0104
U 1 1 5EE780CB
P 2150 5250
F 0 "#PWR0104" H 2150 5000 50  0001 C CNN
F 1 "GND" H 2155 5077 50  0000 C CNN
F 2 "" H 2150 5250 50  0001 C CNN
F 3 "" H 2150 5250 50  0001 C CNN
	1    2150 5250
	1    0    0    -1  
$EndComp
Connection ~ 2150 5250
$Comp
L Device:R_POT RV1
U 1 1 5EEC4030
P 7050 3850
F 0 "RV1" V 6843 3850 50  0000 C CNN
F 1 "10k lin" V 6934 3850 50  0000 C CNN
F 2 "Potentiometer_THT:Potentiometer_ACP_CA9-H2,5_Horizontal" H 7050 3850 50  0001 C CNN
F 3 "~" H 7050 3850 50  0001 C CNN
	1    7050 3850
	0    1    1    0   
$EndComp
$Comp
L Connector_Generic:Conn_01x09 J5
U 1 1 5EEDA1D6
P 7700 4950
F 0 "J5" H 7650 5600 50  0000 L CNN
F 1 "Display" H 7650 5500 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x09_P2.54mm_Vertical" H 7700 4950 50  0001 C CNN
F 3 "~" H 7700 4950 50  0001 C CNN
	1    7700 4950
	1    0    0    -1  
$EndComp
Wire Wire Line
	6900 3850 6900 4150
Wire Wire Line
	6900 4150 7400 4150
Wire Wire Line
	7500 4750 7050 4750
Wire Wire Line
	7050 4750 7050 4000
Wire Wire Line
	7500 5250 6850 5250
Wire Wire Line
	6850 5250 6850 3650
Wire Wire Line
	6850 3650 2000 3650
Wire Wire Line
	7500 4650 7300 4650
Wire Wire Line
	7300 4650 7300 3850
Wire Wire Line
	7200 3850 7300 3850
Connection ~ 7300 3850
Wire Wire Line
	7300 3850 7300 3750
Wire Wire Line
	5950 4850 7500 4850
Wire Wire Line
	6550 4950 7500 4950
Wire Wire Line
	6650 5050 7500 5050
Wire Wire Line
	7400 4150 7400 4550
Wire Wire Line
	7500 4550 7400 4550
Connection ~ 7400 4550
$Comp
L Connector_Generic:Conn_01x03 J1
U 1 1 5FCD689F
P 6700 4550
F 0 "J1" H 6400 4850 50  0000 L CNN
F 1 "SerialPort" H 6400 4750 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 6700 4550 50  0001 C CNN
F 3 "~" H 6700 4550 50  0001 C CNN
	1    6700 4550
	1    0    0    -1  
$EndComp
Wire Wire Line
	5950 4450 6500 4450
Wire Wire Line
	5950 4550 6500 4550
$Comp
L power:GND #PWR0105
U 1 1 5FCE4005
P 6400 4650
F 0 "#PWR0105" H 6400 4400 50  0001 C CNN
F 1 "GND" H 6405 4477 50  0000 C CNN
F 2 "" H 6400 4650 50  0001 C CNN
F 3 "" H 6400 4650 50  0001 C CNN
	1    6400 4650
	1    0    0    -1  
$EndComp
Wire Wire Line
	6500 4650 6400 4650
$Comp
L Transistor_BJT:BC237 Q1
U 1 1 5FCF4084
P 2850 5900
F 0 "Q1" H 3041 5946 50  0000 L CNN
F 1 "BC237" H 3041 5855 50  0000 L CNN
F 2 "Package_TO_SOT_THT:TO-92_Inline" H 3050 5825 50  0001 L CIN
F 3 "http://www.onsemi.com/pub_link/Collateral/BC237-D.PDF" H 2850 5900 50  0001 L CNN
	1    2850 5900
	-1   0    0    -1  
$EndComp
Wire Wire Line
	5950 4750 6950 4750
Wire Wire Line
	6950 4750 6950 5150
Wire Wire Line
	6950 5150 7500 5150
Wire Wire Line
	7400 4550 7400 5400
Wire Wire Line
	7300 4650 7300 5350
Wire Wire Line
	7300 5350 7500 5350
Connection ~ 7300 4650
$Comp
L Diode_Bridge:B250C1500G D5
U 1 1 5FD1DE85
P 3500 2200
F 0 "D5" H 3400 2700 50  0000 L CNN
F 1 "B250C1500G" H 3150 2600 50  0000 L CNN
F 2 "Diode_THT:Diode_Bridge_Round_D9.8mm" H 3650 2325 50  0001 L CNN
F 3 "https://www.vishay.com/docs/88501/b40c1500g.pdf" H 3500 2200 50  0001 C CNN
	1    3500 2200
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H1
U 1 1 5FD33151
P 900 6500
F 0 "H1" H 1000 6546 50  0000 L CNN
F 1 "MountingHole" H 1000 6455 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_Pad" H 900 6500 50  0001 C CNN
F 3 "~" H 900 6500 50  0001 C CNN
	1    900  6500
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H2
U 1 1 5FD336F1
P 900 6750
F 0 "H2" H 1000 6796 50  0000 L CNN
F 1 "MountingHole" H 1000 6705 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_Pad" H 900 6750 50  0001 C CNN
F 3 "~" H 900 6750 50  0001 C CNN
	1    900  6750
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H3
U 1 1 5FD33F46
P 900 7000
F 0 "H3" H 1000 7046 50  0000 L CNN
F 1 "MountingHole" H 1000 6955 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_Pad" H 900 7000 50  0001 C CNN
F 3 "~" H 900 7000 50  0001 C CNN
	1    900  7000
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole_Pad H4
U 1 1 5FD3487E
P 900 7300
F 0 "H4" H 1000 7349 50  0000 L CNN
F 1 "MountingHole_Pad" H 1000 7258 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_Pad_Via" H 900 7300 50  0001 C CNN
F 3 "~" H 900 7300 50  0001 C CNN
	1    900  7300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR01
U 1 1 5FD35555
P 900 7400
F 0 "#PWR01" H 900 7150 50  0001 C CNN
F 1 "GND" H 905 7227 50  0000 C CNN
F 2 "" H 900 7400 50  0001 C CNN
F 3 "" H 900 7400 50  0001 C CNN
	1    900  7400
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H5
U 1 1 5FD4558C
P 1250 6500
F 0 "H5" H 1350 6546 50  0000 L CNN
F 1 "MountingHole" H 1350 6455 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_Pad" H 1250 6500 50  0001 C CNN
F 3 "~" H 1250 6500 50  0001 C CNN
	1    1250 6500
	1    0    0    -1  
$EndComp
$Comp
L Mechanical:MountingHole H6
U 1 1 5FD45592
P 1250 6750
F 0 "H6" H 1350 6796 50  0000 L CNN
F 1 "MountingHole" H 1350 6705 50  0000 L CNN
F 2 "MountingHole:MountingHole_3.2mm_M3_Pad" H 1250 6750 50  0001 C CNN
F 3 "~" H 1250 6750 50  0001 C CNN
	1    1250 6750
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x03 J4
U 1 1 5FCB183B
P 7700 2950
F 0 "J4" H 7780 2992 50  0000 L CNN
F 1 "GPSDO Power" H 7780 2901 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Vertical" H 7700 2950 50  0001 C CNN
F 3 "~" H 7700 2950 50  0001 C CNN
	1    7700 2950
	1    0    0    -1  
$EndComp
Wire Wire Line
	6300 2850 7500 2850
Wire Wire Line
	6300 3150 7400 3150
Wire Wire Line
	7400 3150 7400 3050
Wire Wire Line
	7400 2950 7500 2950
Connection ~ 6300 3150
Wire Wire Line
	7500 3050 7400 3050
Connection ~ 7400 3050
Wire Wire Line
	7400 3050 7400 2950
Wire Wire Line
	3000 4400 3050 4400
NoConn ~ 4400 4050
NoConn ~ 4400 4150
NoConn ~ 4400 4450
NoConn ~ 4400 4550
NoConn ~ 4400 4650
NoConn ~ 4400 4750
NoConn ~ 4400 4850
NoConn ~ 4400 4950
NoConn ~ 4400 5050
NoConn ~ 4400 5150
NoConn ~ 4400 5650
NoConn ~ 4400 5950
NoConn ~ 5950 5950
NoConn ~ 5950 5850
NoConn ~ 5950 5750
NoConn ~ 5950 5650
NoConn ~ 5950 5550
NoConn ~ 5950 5450
NoConn ~ 5950 4950
NoConn ~ 5950 4650
NoConn ~ 5950 4350
NoConn ~ 5950 4250
Wire Wire Line
	1700 2200 2150 2200
Wire Wire Line
	2150 2200 2150 2400
Wire Wire Line
	1900 3150 1900 2300
Wire Wire Line
	1900 2300 1700 2300
$EndSCHEMATC
