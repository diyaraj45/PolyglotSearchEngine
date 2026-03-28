#Import and use Flask to create the bridge between frontend and backend
#request receives the data sent from website and jsonify is used to send the response back to the frontend in JSON format
from flask import Flask, request, jsonify
from flask_cors import CORS #to allow cross-origin requests from frontend to backend
web = Flask(__name__) #create backend web program, __name__ is a built in Python value Flask it is used internally.
CORS(web) #enable CORS for the web app
#create a route
@web.route("/")
def home():
    return "Bridge is working" #to check if working.
#create a route which is called "/search" and accepts POST requests- to send the word to search for
@web.route("/search", methods=["POST"])
def search():
    #get the JSON data sent from website
    data = request.get_json()
    word = data["word"] #extract the word to search for

    #for now fake results
    return jsonify({
        "word": word,
        "trieResult": "Fake Trie Result",
        "trieTime": 123,
        "hashResult": "Fake Hash Result",
        "hashTime": 456
    })

#This is what starts backend when run.

if __name__ == "__main__":
    web.run(debug=True)
