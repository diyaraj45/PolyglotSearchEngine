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

    # run the C++ program
    import subprocess
    result = subprocess.run(
        ["program.exe"],
        input=word + "\n",  # send the word as input to the C++ program
        capture_output=True, #capture what the program prints
        text=True #treat the output as text
    )

    #get all printed output from the C++ program
    output = result.stdout.splitlines()

    #default response if word not found
    response_data = {
        "word": word,
        "trieResult": "Word not found",
        "trieTime": "0 ns",
        "hashResult": "Word not found",
        "hashTime": "0 ns"
    }

    #read each printed line and extract values
    for line in output:
        if line.startswith("Word:"):
            response_data["word"] = line.replace("Word:", "").strip()
        elif line.startswith("TrieResult:"):
            response_data["trieResult"] = line.replace("TrieResult:", "").strip()
        elif line.startswith("TrieTime:"):
            response_data["trieTime"] = line.replace("TrieTime:", "").strip()
        elif line.startswith("HashResult:"):
            response_data["hashResult"] = line.replace("HashResult:", "").strip()
        elif line.startswith("HashTime:"):
            response_data["hashTime"] = line.replace("HashTime:", "").strip()
    #send the real results back to web
    return jsonify(response_data)

#This is what starts backend when run.

if __name__ == "__main__":
    web.run(debug=True)



