#  C-Project: Mood Detector and Enhancer
Artificially Intelligent software to detect user's mood based on the text entered. After that it entertains user 
based on mood. Mood is predicted on the basis of text entered. 
It stores things which make user happy and when user is not happy it suggests activities which made user happy previously. Moreover, it has a diary option which stores good 
experiences of life and then displays to user in case of unhappy mood.

### Software has:
- Password 
- Basic Encyption of password before storing in file
- Detecting user's mood and entertaining accordingly based on words entered
- Option to write diary if user is happy
- Option to read diary if user is not happy

### Code Features:
- Modular design
- Well commented code
- Text file to array convertor
- Search engine for words stored in text files
- Natural Language Processing


### Directory Structure:
- "SoftwareFiles" folder includes files in which data is stored at execution of software for later usage
such as encrypted password and name of user.

- Libraries folders include words which are compared with entered text to predict the mood of the user.
There is a separate file for Quote of the day.

### Basic Logic of Flow of Execution:
Whatever user enters is converted in separate words using 2D arrays in C (generally known as String arrays). Each slot of
array stores a word entered by user. Something between spaces represents a word. 
Those words are compared with all the words in the libraries. If a word which indicated happiness is detected then mood is
labeled as "happy". If "not" is detected along with happy mood indicating word then mood is labeled as "sad". There are about 7 categories of mood. Different options are shown for each category.

If user is happy then he/she is asked from a list of activities to let program know what she/he was doing. Then that is stored
to for future suggestions to make user happy.
Morover, if user is happy then through diary option user can store experiences of the day. In case of unhappy mood, program gives choice to user to read memories from good days along with activity suggestions.
