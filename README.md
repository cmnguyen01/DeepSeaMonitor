# DeepSeaMonitor
CptS 423 Capstone
As team Baldur this our Capstone Project to design a system that will monitor the hardware for a submarine during deep-sea exploration under the requirement that it run on linux as that is the OS the company uses and that it is written in C#. Each sensor send UDP packets through ethernet connection. Our server acts as the reciever that will decode the UDP packets and store them in the database.

# Backend
This is done within our backend loads the coded data into a datahandler. The data handler deciphers the content of the packages and it sends the value to be recorded on long term memory in the form of a binary file. Once that is accomplished, the decoded value is sent to the front-end portion of the project.
 
 # Front End
 Utilizes the decrypted data from the back end and display the results to the user. The user is able to see previous mission data that is stored in the database to compare. The data can be viewed in realtime either in a table format or a graph fomrat.
