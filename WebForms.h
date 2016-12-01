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

  static String GetPickLine(String mode, String modeName, String displayName)
  {
    String checked = mode == modeName ? "checked" : "";
    
    return String("<tr><td>") +
        "  <input type=\"radio\" name=\"Mode\" value=\"" + modeName + "\" " + checked + ">" + displayName + "<br>" +
        "</td></tr>";
  }

  static String GetWebForm(LEDState& ledState)
  {
    return
    String("") +

    
    "<title>Garage LEDs</title><h1>Garage LEDs</h1>" +
"" +
"<form method=\"post\">" +
"" +
"<table>" +
"<tr><td><h3>Effects</h3></td></tr>" +
  GetPickLine(ledState.Mode, String("Off"), String("Off")) +
  GetPickLine(ledState.Mode, String("White"), String("White")) +
  GetPickLine(ledState.Mode, String("WhiteDim"), String("White Dim")) +
  GetPickLine(ledState.Mode, String("RGBColorFade"), String("RGB Color Fade (RGB, Time)")) +
  GetPickLine(ledState.Mode, String("Alternating"), String("Alternating Colors (RGB, Time, Cycle)")) +
  GetPickLine(ledState.Mode, String("Rainbow"), String("Rainbow")) +
  GetPickLine(ledState.Mode, String("RainbowMirror"), String("Rainbow Mirror")) +
  GetPickLine(ledState.Mode, String("Seahawks"), String("Seahawks")) +
  GetPickLine(ledState.Mode, String("Huskies"), String("Huskies")) +
"<tr><td>&nbsp;</td></tr>" +
"<tr><td><h3>Parameters</h3></td></tr>" +
"<tr><td>" +
"RGB Values: <input type=\"text\" id=\"RGBValues\" name=\"RGBValues\" value=\"" + ledState.RGBValues + "\"/>" +
"</td></tr>" +
"<tr><td>" +
"Time In Seconds: <input type=\"text\" id=\"Time\" name=\"Time\" value=\"" + String(ledState.TimeInSeconds) + "\"/>" +
"</td></tr>" +
"<tr><td>" +
"Cycle Count: <input type=\"text\" id=\"CycleCount\" name=\"CycleCount\" value=\"" + String(ledState.CycleCount) + "\"/>" +
"</td></tr>" +
"<tr><td>" +
"<button type=\"submit\">Engage</button></td></tr>" +
"</table>" +
"" +
"</form>" +


    "";
  }



  
};

