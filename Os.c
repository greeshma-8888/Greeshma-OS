#include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <time.h>
 typedef enum {
 INFO,
 WARN,
 ERROR
 } LogLevel;
 LogLevel currentLogLevel = INFO;
 void setIndiaTimeZone() {
 setenv("TZ", "Asia/Kolkata", 1);
 tzset();
 }
 void getTimestamp(char* buffer, size_t size) {
 time_t now = time(NULL);
 struct tm* t = localtime(&now);
 strftime(buffer, size, "%Y-%m-%d %H:%M:%S", t);
 }
 void logMessage(LogLevel level, const char* message) {
 if (level < currentLogLevel) return;
 char timestamp[100];
 getTimestamp(timestamp, sizeof(timestamp));
 const char* levelStr;
 const char* colorCode;
 switch (level) {
 case INFO:
 levelStr = "INFO";
 colorCode = "\033[0;34m";
 break;
 case WARN:
 levelStr = "WARN";
 colorCode = "\033[0;33m";
 break;
 case ERROR:
 levelStr = "ERROR";
 colorCode = "\033[0;31m";
 break;
 }
 printf("%s[%s] [%s] %s\033[0m\n", colorCode, timestamp, levelStr, message);
 }
void setLogLevel(LogLevel level) {
 currentLogLevel = level;
 }
 int main() {
 setIndiaTimeZone();
 setLogLevel(INFO);
 logMessage(INFO, "This is an info message.");
 logMessage(WARN, "This is a warning message.");
 logMessage(ERROR, "This is an error message.");
 return 0;
 }
