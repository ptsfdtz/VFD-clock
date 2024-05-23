float temperature = 0;
float humidity = 0;
int err = SimpleDHTErrSuccess;

//串口打印温度湿度到电脑
bool flag=0;
void Printf_DHT22_to_PC()//一边打印，一边读取
{
  //DHT22需要0.5Hz的运行速度
  if((Clock.getSecond()&0x01)&&flag==1)//每隔一秒执行一次，即每到奇数秒时，执行下面的函数，在计算机中存储的都是二进制，奇数的最后一位必是1
  {
    flag=0;
    if ((err = dht22.read2(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess)//读取温度湿度
    {
      Serial.print("Read DHT22 failed, err="); Serial.println(err);
      return;
    }
    Serial.print((float)temperature); Serial.print(" °C, ");
    Serial.print((float)humidity); Serial.println(" RH%");
  }
  if(!(Clock.getSecond()&0x01))//在秒数为偶数时才将flag值1
  {
    flag=1;
  }
}
//uint8_t a=0,b=0,c=0,d=0,e=0,f=0,g=0,h=0;//0000 0000
//uint16_t temp=0;
//uint8_t i=0;
void VFD_display_temperature()//VFD屏显示温度程序，上面的函数已经读取过一次温度湿度了，就不再读取了，直接用
{
  static uint8_t i;
  temp=(uint16_t)(temperature*100);
  a=temp/1000;
  b=temp%1000/100;
  d=temp%100/10;
  e=temp%10;

  S1201_WriteOneChar(0, a);
  S1201_WriteOneChar(1, b);
  S1201_WriteOneChar(2, '.'-0x30);
  S1201_WriteOneChar(3, d);
  S1201_WriteOneChar(4, e);
  S1201_WriteOneChar(5, 0xEF-0x30);//显示字符 °
  S1201_WriteOneChar(6, 'C'-0x30);
  i++;
  if(i>3)
  {
    i=0;
  }
  switch(i)
  {
    case 0: S1201_WriteOneChar(7, 0x2D-0x30);break;
    case 1: S1201_WriteOneChar(7, 0x5C-0x30);break;
    case 2: S1201_WriteOneChar(7, 0x7C-0x30);break;
    case 3: S1201_WriteOneChar(7, 0x2F-0x30);break;
  }
 
}

void VFD_display_humidity()//VFD屏显示湿度程序，上面的函数已经读取过一次温度湿度了，就不再读取了，直接用
{
  temp=(uint16_t)(humidity*100);
  a=temp/1000;
  b=temp%1000/100;
  d=temp%100/10;
  e=temp%10;

  S1201_WriteOneChar(0, a);
  S1201_WriteOneChar(1, b);
  S1201_WriteOneChar(2, '.'-0x30);
  S1201_WriteOneChar(3, d);
  S1201_WriteOneChar(4, e);
  S1201_WriteOneChar(5, 'R'-0x30);//显示字符 °
  S1201_WriteOneChar(6, 'H'-0x30);
  S1201_WriteOneChar(7, '%'-0x30);
}
