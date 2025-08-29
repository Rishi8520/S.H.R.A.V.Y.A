import http.server, socketserver, pyttsx3, json, threading

PORT = 8888            # n8n will POST here
engine = pyttsx3.init()

class Handler(http.server.SimpleHTTPRequestHandler):
    def do_POST(self):
        length = int(self.headers['Content-Length'])
        body   = self.rfile.read(length).decode()
        try:
            data = json.loads(body)
            text = data.get("text", "")
            if text:
                threading.Thread(target=say, args=(text,)).start()
        except json.JSONDecodeError:
            pass
        self.send_response(204); self.end_headers()

def say(text):
    engine.say(text)
    engine.runAndWait()

print(f"🔊 SHRAVYA speaker listening on http://localhost:{PORT}")
socketserver.TCPServer(("", PORT), Handler).serve_forever()
