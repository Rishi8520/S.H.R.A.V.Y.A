#!/usr/bin/env python3
"""
Simple HTTP server to serve the SHRAVYA HTML file
Run this in the directory containing shravya.html
"""

import http.server
import socketserver
import os
import webbrowser
from pathlib import Path

# Configuration
PORT = 8000
HTML_FILE = "shravya.html"

class CustomHandler(http.server.SimpleHTTPRequestHandler):
    def end_headers(self):
        # Add CORS headers
        self.send_header('Access-Control-Allow-Origin', '*')
        self.send_header('Access-Control-Allow-Methods', 'GET, POST, OPTIONS')
        self.send_header('Access-Control-Allow-Headers', 'Content-Type')
        super().end_headers()

def main():
    # Check if HTML file exists
    if not Path(HTML_FILE).exists():
        print(f"Error: {HTML_FILE} not found in current directory")
        print(f"Current directory: {os.getcwd()}")
        return
    
    # Start server
    with socketserver.TCPServer(("", PORT), CustomHandler) as httpd:
        print(f"✅ Serving {HTML_FILE} at http://localhost:{PORT}/{HTML_FILE}")
        print(f"🔗 Direct link: http://localhost:{PORT}/{HTML_FILE}")
        print(f"📝 n8n webhook URL: http://localhost:5678/webhook/shravya-voice")
        print("\nPress Ctrl+C to stop the server")
        
        # Optional: Open browser automatically
        # webbrowser.open(f"http://localhost:{PORT}/{HTML_FILE}")
        
        try:
            httpd.serve_forever()
        except KeyboardInterrupt:
            print("\n🛑 Server stopped")

if __name__ == "__main__":
    main()
