void setup()
{
    Serial.begin(9600);
    pinMode(13,OUTPUT);
}

int input,num;
int buff[5];
int j=-1;

int calc()
{
    int num=0,x=0;
 
    for(x;x<=j;x++)
          num=num+(buff[x]-48)*pow(10,j-x);
 
    return num;
}
 

 
void loop()
{
    if(Serial.available()>0)
    {
        digitalWrite(13,HIGH);
        input=Serial.read();
 
        if(input==',')
        {
            num=calc();
            j=-1;
            Serial.println(num);
        }
        else
        {
            j++;
            buff[j]=input;
        }
    }
    else
    {
      //digitalWrite(13,LOW);  
    }
}
