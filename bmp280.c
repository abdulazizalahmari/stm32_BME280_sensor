/////////////////////////////////////////////////////////////////////////////////////////BMP280
	uint8_t   ADRESS_BMP280=237 ;//118 <<1= 236 or 119<<1=238
	signed int pressure;
int16_t temp;
uint16_t dig_t1;
int16_t dig_t2;
int16_t dig_t3;

uint16_t dig_p1;
int16_t dig_p2;
int16_t dig_p3;
int16_t dig_p4;
int16_t dig_p5;
int16_t dig_p6;
int16_t dig_p7;
int16_t dig_p8;
int16_t dig_p9;

uint16_t dig_T1;
int16_t dig_T2;
int16_t dig_T3;
uint16_t dig_P1;
int16_t dig_P2;
int16_t dig_P3;
int16_t dig_P4;
int16_t dig_P5;
int16_t dig_P6;
int16_t dig_P7;
int16_t dig_P8;
int16_t dig_P9;
	signed extra;
int64_t var1;
int64_t  var2;
int32_t var11;
int32_t  var22;
	int32_t t_fine;
extern	int32_t T;
int32_t T;
extern	uint8_t T8[4];
uint8_t T8[4];
int32_t adc_t;int32_t adc_t1;
int32_t adc_T;
extern uint32_t P;
uint32_t P;
extern uint8_t P8[4];
uint8_t P8[4];
//uint32_t P;
int32_t t;

int32_t adc_p1;
int32_t adc_p;
int32_t adc_P;
uint8_t BMP280_REGESTER[50];uint8_t BMP280_DATA[50];

char BMP280_DATA1[500];uint8_t BMP280_DATA2[200];
char BMP280_DATA3[300];uint8_t BMP280_DATA4[300];


double DATA=1.1;
 //#define GYRO_CONFIG 24 //0b00011000;///7:5 self test 4:3 GYRO_FS_SEL 00 250 01 500 10 1000 11 2000  2 reserved 1:0 FCOICE_B 00 bescause DLPF_CFG
 #define GYRO_CONFIG 0 //0b00000000;///7:5 self test 4:3 GYRO_FS_SEL 00 250 01 500 10 1000 11 2000  2 reserved 1:0 FCOICE_B 00 bescause DLPF_CFG
 //#define ACCEL_CONFIG  24  // 0b00011000;///7:5 slef test 4:3 ACCELFS_SEL 00 2g 01 4g 10 8g 11 16g 2:0 reserved
  #define ACCEL_CONFIG  0  // 0b00000000;///7:5 slef test 4:3 ACCELFS_SEL 00 2g 01 4g 10 8g 11 16g 2:0 reserved
 #define	ACCEL_CONFIG_2 8 //0b00001000; ///7:4 reserverd 4 ACCEL_FCHOICE_B=1 2:0A_DLPF_CFG=000 doesnt matter
  #define USER_CTRL 0 //7 DMP_EN 0 6 FIFO_EN 0 5 I2C_MST_EN 0 4 I2C_IF_DIS 0 3 DMP_RST 0 2 FIFO_RST 0 1 I2C_MST_RST 0 0  SIG_COND_RST 0
	#define PWR_MGMT_1  0  // 7 DEVICE_RESET 0  6 SLEEP 0  5 CYCLE 0 4 GYRO_STANDBY 0  3 TEMP_DIS 0 2:0 CLKSEL 0
	#define	PWR_MGMT_2 0 //7:6 LP_WAKE_CTRL[1:0] 00 dont care  5:0 DISABLE_XA for gyro and accel set 0 on
void   GET_TEMP_BMP280()
{
var1 = ((((adc_T>>3) - ((int32_t)dig_T1<<1))) * ((int32_t)dig_T2)) >> 11;
var2 = (((((adc_T>>4) - ((int32_t)dig_T1)) * ((adc_T>>4) - ((int32_t)dig_T1))) >> 12) *((int32_t)dig_T3)) >> 14;
t_fine = var1 + var2;
T = (t_fine * 5 + 128) >> 8;
T8[3]=T>>(8+8+8);
T8[2]=T>>(8+8);
T8[1]=T>>(8);
T8[0]=T;
//return T;
}
// Returns pressure in Pa as unsigned 32 bit integer in Q24.8 format (24 integer bits and 8 fractional bits).
// Output value of “24674867” represents 24674867/256 = 96386.2 Pa = 963.862 hPa
int64_t  GET_Pressure_BMP280(  )
{
//int32_t var1, var2;
//uint32_t p;
var1 = (((int32_t)t_fine)>>1) - (int32_t)64000;
var2 = (((var1>>2) * (var1>>2)) >> 11 ) * ((int32_t)dig_P6);
var2 = var2 + ((var1*((int32_t)dig_P5))<<1);
var2 = (var2>>2)+(((int32_t)dig_P4)<<16);
var1 = (((dig_P3 * (((var1>>2) * (var1>>2)) >> 13 )) >> 3) + ((((int32_t)dig_P2) * var1)>>1))>>18;
var1 =((((32768+var1))*((int32_t)dig_P1))>>15);
if (var1 == 0)
{
	
return 0; // avoid exception caused by division by zero
}
P = (((uint32_t)(((int32_t)1048576)-adc_P)-(var2>>12)))*3125;
if (P < 0x80000000)
{
P = (P << 1) / ((uint32_t)var1);
}
else
{
P = (P / (uint32_t)var1) * 2;
}
var1 = (((int32_t)dig_P9) * ((int32_t)(((P>>3) * (P>>3))>>13)))>>12;
var2 = (((int32_t)(P>>2)) * ((int32_t)dig_P8))>>13;
P = (uint32_t)((int32_t)P + ((var1 + var2 + dig_P7) >> 4));
P8[3]=P>>(0);
P8[2]=P>>(8);
P8[1]=P>>(8+8);
P8[0]=P>>(8+8+8);
return P;
}
void   INIT_BMP280()
{
		BMP280_REGESTER[0]=0xF4;// adress for config
		BMP280_REGESTER[1]=0xff;// F4
		BMP280_REGESTER[2]=0x80;// ctrl meas
		BMP280_REGESTER[3]=0xfa;// temp adress			BMP280_REGESTER[7]=0x88;// dig_T1 adress
		BMP280_REGESTER[7]=0x88;;// dig_T1 adress
		BMP280_REGESTER[34]=0xF7;// PRSSURE DATA ADRESS

				HAL_I2C_Master_Transmit(&I2C1_Handle, ADRESS_BMP280, &BMP280_REGESTER[0], 3,1000);

}
void   READ_BMP280()
{

			HAL_I2C_Master_Transmit(&I2C1_Handle, ADRESS_BMP280, &BMP280_REGESTER[7], 1,1000);
					HAL_I2C_Master_Receive(&I2C1_Handle, ADRESS_BMP280,&BMP280_REGESTER[8], 24,1000);
					
					dig_t1=(BMP280_REGESTER[9]<<8 |BMP280_REGESTER[8]);
					dig_t2=(BMP280_REGESTER[11]<<8 |BMP280_REGESTER[10]);
						dig_t3=(BMP280_REGESTER[13]<<8 |BMP280_REGESTER[12]);
					dig_p1=(BMP280_REGESTER[15]<<8 |BMP280_REGESTER[14]);
					dig_p2=(BMP280_REGESTER[17]<<8 |BMP280_REGESTER[16]);
						dig_p3=(BMP280_REGESTER[19]<<8 |BMP280_REGESTER[18]);
					dig_p4=(BMP280_REGESTER[21]<<8 |BMP280_REGESTER[20]);
					dig_p5=(BMP280_REGESTER[23]<<8 |BMP280_REGESTER[22]);
						dig_p6=(BMP280_REGESTER[25]<<8 |BMP280_REGESTER[24]);
					dig_p7=(BMP280_REGESTER[27]<<8 |BMP280_REGESTER[26]);
					dig_p8=(BMP280_REGESTER[29]<<8 |BMP280_REGESTER[28]);
						dig_p9=(BMP280_REGESTER[31]<<8 |BMP280_REGESTER[30]);
						dig_P1=dig_p1;	dig_P2=dig_p2;	dig_P3=dig_p3;	dig_P4=dig_p4;	dig_P5=dig_p5;	dig_P6=dig_p6;dig_P7=dig_p7;	dig_P8=dig_p8;	dig_P9=dig_p9;
						dig_T1=dig_t1;dig_T2=dig_t2;dig_T3=dig_t3;
						
					
	HAL_I2C_Master_Transmit(&I2C1_Handle, ADRESS_BMP280, &BMP280_REGESTER[3], 1,1000);
	HAL_I2C_Master_Receive(&I2C1_Handle, ADRESS_BMP280,&BMP280_REGESTER[4], 3,100);
	HAL_I2C_Master_Transmit(&I2C1_Handle, ADRESS_BMP280, &BMP280_REGESTER[34], 1,1000);
	HAL_I2C_Master_Receive(&I2C1_Handle, ADRESS_BMP280,&BMP280_REGESTER[35], 3,1000);
					
					
					adc_t1=(BMP280_REGESTER[4]<<12 |BMP280_REGESTER[5]<<4|BMP280_REGESTER[6]>>4);adc_t=adc_t1;
					 adc_T=adc_t;
					adc_p1=(BMP280_REGESTER[35]<<12|BMP280_REGESTER[36]<<4|BMP280_REGESTER[37]>>4);adc_p=adc_p1;
					adc_P=adc_p;
}