// The author disclaims copyright to this source code.
#include "WiFiComponent.h"
#include "Debug.h"

WiFiComponent::WiFiComponent(const char* ssid, const char* password) {
	server = new ESP8266WebServer(80);
	ap_id = ssid;
	ap_password = password;
}

WiFiComponent::~WiFiComponent() {
}

template <typename T>
struct Callback;

template <typename Ret, typename... Params>
struct Callback<Ret(Params...)> {
    template <typename... Args>
    static Ret callback(Args... args) { return func(args...); }
    static std::function<Ret(Params...)> func;
};

// Initialize the static member.
template <typename Ret, typename... Params>
std::function<Ret(Params...)> Callback<Ret(Params...)>::func;

void WiFiComponent::setup() {
	Debug::getInstance()->debug("WiFiComponent::setup");
	WiFi.disconnect(true);
	delay(1000);

	//callback from C to C++ needs static function
	WiFi.onEvent(reinterpret_cast<WiFiEventCb>(WiFiComponent::onEvent));

	WiFi.begin(ap_id, ap_password);

	server->on("/", [&]() {
		sendMainpage();
	});
	server->on("/graph.svg", [&]() {
		sendGraph();
	});
	server->onNotFound([&]() {
		sendNotFound();
	});
}

void WiFiComponent::process(void) {
	// print status changes only once
	wl_status_t status = WiFi.status();
	boolean statusChanged = status ^ previousStatus;
	previousStatus = status;
	switch (status) {
	case WL_CONNECTED:
		if (statusChanged) {
			Debug::getInstance()->info("WiFiComponent::process WL_CONNECTED");
			server->begin();
		}
		server->handleClient();
		break;
	case WL_IDLE_STATUS:
		if (statusChanged) {
			Debug::getInstance()->info("WiFiComponent::process WL_IDLE_STATUS");
		}
		break;
	case WL_NO_SSID_AVAIL:
		if (statusChanged) {
			Debug::getInstance()->info("WiFiComponent::process WL_NO_SSID_AVAIL");
		}
		break;
	case WL_SCAN_COMPLETED:
		if (statusChanged) {
			Debug::getInstance()->info("WiFiComponent::process WL_SCAN_COMPLETED");
		}
		break;
	case WL_CONNECT_FAILED:
		if (statusChanged) {
			Debug::getInstance()->info("WiFiComponent::process WL_CONNECT_FAILED");
		}
		break;
	case WL_CONNECTION_LOST:
		if (statusChanged) {
			Debug::getInstance()->info("WiFiComponent::process WL_CONNECTION_LOST");
			server->close();
		}
		break;
	case WL_DISCONNECTED:
		if (statusChanged) {
			Debug::getInstance()->info("WiFiComponent::process WL_DISCONNECTED");
		}
		break;
	default:
		break;
	};
}

void WiFiComponent::onEvent(WiFiEvent_t event) {

	switch (event) {
	case WIFI_EVENT_STAMODE_CONNECTED:
		Debug::getInstance()->info("WiFiComponent::onEvent WIFI_EVENT_STAMODE_CONNECTED");
		break;
	case WIFI_EVENT_STAMODE_DISCONNECTED:
		Debug::getInstance()->info("WiFiComponent::onEvent WIFI_EVENT_STAMODE_DISCONNECTED");
		break;
	case WIFI_EVENT_STAMODE_AUTHMODE_CHANGE:
		Debug::getInstance()->info("WiFiComponent::onEvent WIFI_EVENT_STAMODE_AUTHMODE_CHANGE");
		break;
	case WIFI_EVENT_STAMODE_GOT_IP:
		Debug::getInstance()->info(
				"WiFiComponent::onEvent WIFI_EVENT_STAMODE_GOT_IP: " + WiFi.localIP().toString());
		break;
	case WIFI_EVENT_STAMODE_DHCP_TIMEOUT:
		Debug::getInstance()->info("WiFiComponent::onEvent WIFI_EVENT_STAMODE_DHCP_TIMEOUT");
		break;
	case WIFI_EVENT_SOFTAPMODE_STACONNECTED:
		Debug::getInstance()->info("WiFiComponent::onEvent WIFI_EVENT_SOFTAPMODE_STACONNECTED");
		break;
	case WIFI_EVENT_SOFTAPMODE_STADISCONNECTED:
		Debug::getInstance()->info("WiFiComponent::onEvent WIFI_EVENT_SOFTAPMODE_STADISCONNECTED");
		break;
	case WIFI_EVENT_SOFTAPMODE_PROBEREQRECVED:
		Debug::getInstance()->info("WiFiComponent::onEvent WIFI_EVENT_SOFTAPMODE_PROBEREQRECVED");
		break;
	default:
		Debug::getInstance()->error("WiFiComponent::onEvent UNKNOWN EVENT: " + String(event));
		break;
	}
}

void WiFiComponent::sendMainpage() {
	char temp[400];
	snprintf_P(temp, 400,
			"\
<html>\
<head>\
<meta http-equiv='refresh' content='5'/>\
<title>SolarBoilerMeter</title>\
</head>\
<body>\
<h1>SolarBoilerMeter</h1>\
<img src=\"/graph.svg\" />\
</body>\
</html>\
");
	server->send(200, "text/html", temp);
}

void WiFiComponent::sendGraph() {
	String out = "";
	char temp[1000];
	out +=
			"<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"400\" height=\"150\">\n";
	out +=
			"<rect width=\"400\" height=\"150\" fill=\"rgb(250, 230, 210)\" stroke-width=\"1\" stroke=\"rgb(0, 0, 0)\" />\n";
	out += "<g stroke=\"black\">\n";
	int y = rand() % 130;
	for (int x = 10; x < 390; x += 10) {
		int y2 = rand() % 130;
		sprintf(temp,
				"<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke-width=\"1\" />\n",
				x, 140 - y, x + 10, 140 - y2);
		out += temp;
		y = y2;
	}
	out += "</g>\n</svg>\n";

	server->send(200, "image/svg+xml", out);
}

void WiFiComponent::sendNotFound() {
	server->send(404, "text/plain", "Resource not found.");
}
