#include "iwi_SPI_RS0010.h"

//The setup function is called once at startup of the sketch
SPI_RS0010 rs;

void setup()
{
rs.initSPI(50,51,52,53);
}

// The loop function is called in an endless loop
void loop()
{
rs.drawLine(0,0,100,16,1);
rs.displayBuf();
delay(2000);

rs.drawString(0,0,"T E S T",1,1,1);
rs.displayBuf();
delay(2000);

rs.drawBoldString(0,0,"10:45",1,1);
rs.displayBuf();
delay(2000);
}
