  const char startString[] PROGMEM = "<title>Garage LEDs</title><h1>Garage LEDs</h1><form method=\"post\"><table><tr><td><h3>Effects</h3></td></tr>";


class WebForms
{
  public:

  static void parseFormData(ESP8266WebServer& server)
  {
    Serial.print("Commands:");
    Serial.println(server.args());
    
    for ( uint8_t i = 0; i < server.args(); i++ ) {
      Serial.println(server.argName(i));
    }
  }

  static void SendPickLine(ESP8266WebServer& server, String& mode, const char* modeName, const char* displayName)
  {
    String checked = mode == modeName ? "checked" : "";

    char buffer[150];

    sprintf(buffer, "<tr><td><input type=\"radio\" name=\"Mode\" value=\"%s\" %s>%s<br></td></tr>", modeName, checked.c_str(), displayName);
    server.sendContent(buffer);
   
  }

  static void SendWebForm(ESP8266WebServer& server, LEDState& ledState)
  {
    server.setContentLength(CONTENT_LENGTH_UNKNOWN);
    server.send(200, "text/html", "");
 
    return;

    server.sendContent_P(startString);

    SendPickLine(server, ledState.Mode, "Off", "Off");
    SendPickLine(server, ledState.Mode, "White", "White");
    SendPickLine(server, ledState.Mode, "WhiteDim", "White Dim");
    SendPickLine(server, ledState.Mode, "RGBColorFade", "RGB Color Fade (RGB, Time)");
    SendPickLine(server, ledState.Mode, "Alternating", "Alternating Colors (RGB, Time, Cycle)");
    SendPickLine(server, ledState.Mode, "Rainbow", "Rainbow");
    SendPickLine(server, ledState.Mode, "RainbowMirror", "Rainbow Mirror");
    SendPickLine(server, ledState.Mode, "Seahawks", "Seahawks");
    SendPickLine(server, ledState.Mode, "Huskies", "Huskies");

    String contents = 

    String("") +


"<tr><td>&nbsp;</td></tr>" 
"<tr><td><h3>Parameters</h3></td></tr>"
"<tr><td>"
"RGB Values: <input type=\"text\" id=\"RGBValues\" name=\"RGBValues\" value=\"" + ledState.RGBValues + "\"/>"
"</td></tr>"
"<tr><td>"
"Time In Seconds: <input type=\"text\" id=\"Time\" name=\"Time\" value=\"" + String(ledState.TimeInSeconds) + "\"/>"
"</td></tr>"
"<tr><td>"
"Cycle Count: <input type=\"text\" id=\"CycleCount\" name=\"CycleCount\" value=\"" + String(ledState.CycleCount) + "\"/>"
"</td></tr>"
"<tr><td>"
"<button type=\"submit\">Engage</button></td></tr>"
"</table>"
""
"</form>" +


    "";

    server.sendContent(contents);
  }



  
};

