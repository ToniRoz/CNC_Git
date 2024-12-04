/**************************CrowPanel ESP32 HMI Display Example Code************************
Version     :	1.1
Suitable for:	CrowPanel ESP32 HMI Display
Product link:	https://www.elecrow.com/esp32-display-series-hmi-touch-screen.html
Code	  link:	https://github.com/Elecrow-RD/CrowPanel-ESP32-Display-Course-File
Lesson	link:	https://www.youtube.com/watch?v=WHfPH-Kr9XU
Description	:	The code is currently available based on the course on YouTube, 
				        if you have any questions, please refer to the course video: Introduction 
				        to ask questions or feedback.
**************************************************************/
/*
Todo: 
implement password check 
    need to check against data and correct time  
    needs a press and hold option 
    needs a feedrate controller
implement filesearch 
    check if data structure can be read from sd
    get an idea of how to implement a search (check gpt answer)
*/

#include <Wire.h>
#include <FS.h>
#include <SD.h>
#include <SPI.h>
#include "gfx_conf.h"
#include <PCA9557.h>
#include <RTClib.h>


#include <lvgl.h>
#include "ui.h"

/**************************LVGL and UI END************************/

/*******************************************************************************
   Config the display panel and touch panel in gfx_conf.h
 ******************************************************************************/


static lv_disp_draw_buf_t draw_buf;
static lv_color_t disp_draw_buf1[screenWidth * screenHeight / 10];
static lv_color_t disp_draw_buf2[screenWidth * screenHeight / 10];
static lv_disp_drv_t disp_drv;

PCA9557 Out;    //for touch timing init

/**************************SD and Clock************************/

/*******************************************************************************
   
 ******************************************************************************/

#define SD_MOSI 11
#define SD_MISO 13
#define SD_SCK 12
#define SD_CS 10

SPIClass SD_SPI; //SD card
RTC_DS3231 rtc; //clock card

/****************************relevant functions***********************/

int sd_init()
{
  //SD_SPI.begin(SD_SCK, SD_MISO, SD_MOSI);
   SD_SPI.begin(SD_SCK, SD_MISO, SD_MOSI, SD_CS);
  if (!SD.begin(SD_CS, SD_SPI, 80000000))
  {
    Serial.println("Card Mount Failed");
    return 1;
  }
  else
  {
    Serial.println("Card Mount Successed");
  }
  Serial.println("TF Card init over.");
  return 0;
}


/**************************Custom UI functions************************
Functions need to be implemented here as long as i cant figure out how to use c++
functionality in the ui_events.c
**************************************************************/


/**************************password functions************************/
char Code[7];  // Use 7 to include null-terminator for DDMMYY
String fileContents; // Declare a global variable to store file contents
void keyboardDone(lv_event_t * e) // code enter function 
{
	// Get the current date
	DateTime now = rtc.now();
	snprintf(Code, sizeof(Code), "%02d%02d%02d", now.day(), now.month(), now.year() % 100);

	// Debug print
	Serial.println("done activated");
	Serial.print("Current Code (DDMMYY): ");
	Serial.println(Code);

	// Retrieve the entered code
	char enteredCode[7];
	strcpy(enteredCode, lv_textarea_get_text(ui_CodeEnterTextbox)); 
	Serial.print("Entered Code: ");
	Serial.println(enteredCode);

	// Check if the entered code matches the generated code
	if(strcmp(enteredCode, Code) == 0) { 
		lv_obj_clear_state(ui_CodeSubmitButton, LV_STATE_DISABLED);
		lv_obj_add_state(ui_CodeSubmitButton, LV_STATE_CHECKED);
	}
}

/**************************Fileread and program************************/

// Event handler to read file contents and save to variable
void readFileAndSaveToVariable(lv_event_t * e) {
    lv_obj_t * btn = lv_event_get_target(e);
    const char * filename = (const char *)lv_obj_get_user_data(btn); // Get file name from user data

    if (!filename) {
        Serial.println("Error: Filename is NULL");
        return;
    }

    // Add leading slash to the filename for SD card path
    String filepath = String("/") + filename;

    // Open file from SD card
    File file = SD.open(filepath.c_str());
    if (!file) {
        Serial.println("Failed to open file");
        return;
    }

    // Clear any previous content in fileContents
    fileContents = "";

    // Read file contents and store in fileContents
    while (file.available()) {
        fileContents += (char)file.read();
    }
    file.close();

    // Switch to the new screen after reading file
    _ui_screen_change(&ui_RunProgramScreen, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_RunProgramScreen_screen_init);
    _ui_screen_delete(&ui_SelectPropgramScreen);
    String name = extractComponent(fileContents, "Name:", ";");
    lv_label_set_text(ui_RunTaskLabel, name.c_str());
}


String extractComponent(String fileContents, String startDelimiter, String endDelimiter) {
    int startIndex = fileContents.indexOf(startDelimiter);
    if (startIndex == -1) {
        Serial.println("Start delimiter not found");
        return ""; // Start delimiter not found
    }
    startIndex += startDelimiter.length();
    
    int endIndex = fileContents.indexOf(endDelimiter, startIndex);
    if (endIndex == -1) {
        Serial.println("End delimiter not found");
        return ""; // End delimiter not found
    }

    // Extract substring, trim whitespace, and then return
    String component = fileContents.substring(startIndex, endIndex);
    component.trim();
    return component;
}

// Modified listDir function with allocated memory for file names
void listDir(fs::FS & fs, const char *dirname, lv_obj_t * list) {
    Serial.printf("Listing files in directory: %s\n", dirname);

    File root = fs.open(dirname);
    if (!root || !root.isDirectory()) {
        Serial.println("Failed to open directory or not a directory");
        return;
    }

    File file = root.openNextFile();
    while (file) {
        if (!file.isDirectory()) {  // Only process files
            Serial.println(file.name());  // Output file name to Serial

            // Create a button for each file in the list
            lv_obj_t * btn = lv_list_add_btn(list, NULL, file.name());

            // Allocate memory and copy the file name for each button's user data
            char * filename = (char *)lv_mem_alloc(strlen(file.name()) + 1);
            strcpy(filename, file.name());
            lv_obj_set_user_data(btn, filename);

            // Assign event handler to button to read file when clicked
            lv_obj_add_event_cb(btn, readFileAndSaveToVariable, LV_EVENT_CLICKED, NULL);
        }
        file = root.openNextFile();
    }
}

// Free allocated memory after button is deleted
void freeFileName(lv_event_t * e) {
    char * filename = (char *)lv_event_get_user_data(e);
    if (filename) {
        lv_mem_free(filename);
    }
}

void MontagePoint(lv_event_t * e){
  String mp = extractComponent(fileContents, "MP:", ";");
  // Remove the "MP: " prefix and parentheses
  mp.replace("MP:", "");
  mp.replace("(", "");
  mp.replace(")", "");
  mp.trim();  // Clean any leading/trailing whitespace

  // Split the coordinates by comma
  int commaIndex = mp.indexOf(',');
  String xCoord = mp.substring(0, commaIndex);
  String yCoord = mp.substring(commaIndex + 1);

  // Create G-code string to move to this point
  String gcode = "G0 X" + xCoord + " Y" + yCoord + " F1500"; // G0 for rapid movement
  Serial.println(gcode);
}

void RunProgram(lv_event_t * e) {
  String prog = extractComponent(fileContents, "Prog:", ";");
  
  // Split prog by newlines to send each line individually
  int currentIndex = 0;
  int nextIndex = prog.indexOf('\n', currentIndex);
  
  while (nextIndex != -1) {
    // Extract one line of G-code
    String line = prog.substring(currentIndex, nextIndex);
    line.trim(); // Remove any leading/trailing whitespace
    
    // Send the line to the CNC machine
    Serial.println(line);
    delay(3000); // Adjust delay as needed for machine processing time
    
    // Move to the next line
    currentIndex = nextIndex + 1;
    nextIndex = prog.indexOf('\n', currentIndex);
  }
  
  // Send the last line if there's no newline at the end
  String lastLine = prog.substring(currentIndex);
  lastLine.trim();
  if (lastLine.length() > 0) {
    Serial.println(lastLine);
  }
}

/**************************G-code Button Functions************************

**************************************************************/

// these should send g-code
void Increment_Z(lv_event_t * e){
  Serial.println("G91");           // Set to relative positioning
  Serial.println("G0 Z1");          // Move Z up by 1 unit
  Serial.println("G90");           // Return to absolute positioning
}

void Decrement_Z(lv_event_t * e){
  Serial.println("G91");           // Set to relative positioning
  Serial.println("G0 Z-1");         // Move Z down by 1 unit
  Serial.println("G90");           // Return to absolute positioning
}

void Increment_X(lv_event_t * e){
  Serial.println("G91");           // Set to relative positioning
  Serial.println("G0 X1");          // Move X up by 1 unit
  Serial.println("G90");           // Return to absolute positioning
}

void Decrement_X(lv_event_t * e){
  Serial.println("G91");           // Set to relative positioning
  Serial.println("G0 X-1");         // Move X down by 1 unit
  Serial.println("G90");           // Return to absolute positioning
}

void Increment_Y(lv_event_t * e){
  Serial.println("G91");           // Set to relative positioning
  Serial.println("G0 Y1");          // Move Y up by 1 unit
  Serial.println("G90");           // Return to absolute positioning
}



void Decrement_Y(lv_event_t * e){
  Serial.println("G91");           // Set to relative positioning
  Serial.println("G0 Y-1");         // Move Y down by 1 unit
  Serial.println("G90");           // Return to absolute positioning
}

void SetZeroF(lv_event_t * e){
  Serial.println("G92 X0 Y0 Z0");

}

/**************************Touch and standard ui func************************
don't touch these
**************************************************************/

/* Display flushing */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
   uint32_t w = ( area->x2 - area->x1 + 1 );
   uint32_t h = ( area->y2 - area->y1 + 1 );

   tft.pushImageDMA(area->x1, area->y1, w, h,(lgfx::rgb565_t*)&color_p->full);

   lv_disp_flush_ready( disp );

}

void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data)
{
   uint16_t touchX, touchY;
   bool touched = tft.getTouch( &touchX, &touchY);
   if( !touched )
   {
      data->state = LV_INDEV_STATE_REL;
   }
   else
   {
      data->state = LV_INDEV_STATE_PR;

      /*Set the coordinates*/
      data->point.x = touchX;
      data->point.y = touchY;

      //Serial.print( "Data x " );
      //Serial.println( touchX );

      //Serial.print( "Data y " );
      //Serial.println( touchY );
   }
}






void setup()
{
  Serial.begin(115200);
  delay(3000);
  Wire1.begin(GPIO_NUM_19, GPIO_NUM_20); // this might not be the correct way to acces the i2c bus
    
  if (sd_init() == 0)
  {
    Serial.println("TF init success");
  } else {
    Serial.println("TF init fail");
  }

  if (!rtc.begin(&Wire1)) 
  {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  DateTime now = rtc.now();
  Serial.print("Date/Time: ");
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" ");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();

#if defined (CrowPanel_50) || defined (CrowPanel_70)
  pinMode(38, OUTPUT);
  digitalWrite(38, LOW);
  pinMode(17, OUTPUT);
  digitalWrite(17, LOW);
  pinMode(18, OUTPUT);
  digitalWrite(18, LOW);
  pinMode(42, OUTPUT);
  digitalWrite(42, LOW);

  //touch timing init
  Wire.begin(19, 20);
  Out.reset();
  Out.setMode(IO_OUTPUT);
  Out.setState(IO0, IO_LOW);
  Out.setState(IO1, IO_LOW);
  delay(20);
  Out.setState(IO0, IO_HIGH);
  delay(100);
  Out.setMode(IO1, IO_INPUT);

#elif defined (CrowPanel_43)
  pinMode(20, OUTPUT);
  digitalWrite(20, LOW);
  pinMode(19, OUTPUT);
  digitalWrite(19, LOW);
  pinMode(35, OUTPUT);
  digitalWrite(35, LOW);
  pinMode(38, OUTPUT);
  digitalWrite(38, LOW);
  pinMode(0, OUTPUT);//TOUCH-CS
#endif


  //Display Prepare
  tft.begin();
  tft.fillScreen(TFT_BLACK);
  tft.setTextSize(2);
  delay(200);

  lv_init();

  delay(100);

  lv_disp_draw_buf_init(&draw_buf, disp_draw_buf1, disp_draw_buf2, screenWidth * screenHeight/10);
  /* Initialize the display */
  lv_disp_drv_init(&disp_drv);
  /* Change the following line to your display resolution */
  disp_drv.hor_res = screenWidth;
  disp_drv.ver_res = screenHeight;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.full_refresh = 1;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register(&disp_drv);

  /* Initialize the (dummy) input device driver */
  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = my_touchpad_read;
  lv_indev_drv_register(&indev_drv);

  tft.fillScreen(TFT_BLACK);

  ui_init();
  Serial.print("ui init");
  listDir(SD, "/", ui_List1);
  
}


void loop()
{
    lv_timer_handler();
    delay(5);
}
