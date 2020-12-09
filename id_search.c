	
int ii=0;
for(ii=0;ii<=240;ii++){
				if(HAL_I2C_IsDeviceReady(&I2C1_Handle,ii, 1, 100)==HAL_OK){
				//	flgg=1;									
					sprintf( BMP280_DATA3, "\r\n the adress is =%d\r\n",ii);

						for(j=0;j<=99;j++){
		BMP280_DATA4[j]=BMP280_DATA3[j];
		} j=0;
HAL_UART_Transmit(&huart2,&BMP280_DATA4[0],strlen(BMP280_DATA3),3000);
				}
				
 	} ii=0;