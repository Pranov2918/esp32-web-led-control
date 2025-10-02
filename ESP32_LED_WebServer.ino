#include <WiFi.h>

// --- ✏️ 1. REPLACE WITH YOUR WIFI CREDENTIALS ---
const char* ssid = "Your_username";
const char* password = "Your_password";
// ---------------------------------------------

// Create a web server on port 80
WiFiServer server(80);

// This variable will store the HTTP request
String header;

// Define the pin for the built-in LED (usually GPIO 2)
#define LED_PIN 2

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW); // Start with LED off

  // Connect to Wi-Fi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Print local IP address and start web server
  Serial.println("\nWiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          if (currentLine.length() == 0) {
            // HTTP headers always end with a blank line
            // Display the HTML web page
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // Web Page Content
            client.println("<!DOCTYPE html><html>");
            client.println("<head><title>ESP32 Web Server</title>");
            client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");
            
            client.println("<body><h1>ESP32 LED Control</h1>");
            client.println("<p><a href=\"/on\"><button class=\"button\">ON</button></a></p>");
            client.println("<p><a href=\"/off\"><button class=\"button button2\">OFF</button></a></p>");
            client.println("</body></html>");
            client.println();
            
            // Check the request from the browser
            if (header.indexOf("GET /on") >= 0) {
              digitalWrite(LED_PIN, HIGH);
            } else if (header.indexOf("GET /off") >= 0) {
              digitalWrite(LED_PIN, LOW);
            }
            break;
          } else { 
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }
    header = "";
    client.stop();
    Serial.println("Client disconnected.");
  }
}