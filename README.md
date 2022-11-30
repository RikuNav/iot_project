<p style="text-align: center;">
  <img src="readme_images/sql.png" alt="node" style="width:200px;"/>
  </p>
  # Get a Room

Team 4 BITS
  - Alain Vicencio Arizabalo A01620758
  - Fernando Josué Matute A00833375
  - Juan Pablo Martinez Valdivia
  - Ricardo Navarro Gómez A01708825
  - Salvador Rodríguez Paredes A01704562

## <span style="color: rgb(26, 99, 169);">**Neccessity**</span>
The students and collaborators from Tecnológico de Monterrey do not have a clear, direct nor an immediate way of knowing which classrooms are occupied and which aren't in a camps building. This affects the students that want to find an empty classroom to do their activities with no interruptions. This also affects the appropiate consumption of electrical energy, since there are cases where a classroom is not occupied yet the lights are still one. Finally, it also affects the optimization of the patrol routes for the security staff, since they have no way of telling if a classroom is emty when it should be.

## <span style="color: rgb(26, 99, 169);">**Solution**</span>
A web application that allows the Tec community to easily know if a campus classroom is empty or not based on sound and movement sensors, whose results are stored in a data base. 

## <span style="color: rgb(26, 99, 169);">**Software used**</span>
  - MySQL Data Base
  <p style="text-align: center;">
  <img src="readme_images/sql.png" alt="node" style="width:200px;"/>
  <br />
  Download here either one:
  <br />
  XAMPP: https://www.apachefriends.org/index.html
  <br />
  MAMP (Used in our implementation): https://www.mamp.info/en/downloads/
  </p>
  
  - Arduino
  <p style="text-align: center;">
  <img src="readme_images/arduino.png" alt="node" style="width:200px;"/>
  <br />
  Download here:
  <br />
  https://www.arduino.cc/en/software
  </p>
  
  - Node JS
  <p style="text-align: center;">
  <img src="readme_images/nodejs.png" alt="node" style="width:200px;"/>
  <br />
  Download here:
  <br />
  https://nodejs.org/en/download/
  </p>
  
  - React
  <p style="text-align: center;">
  <img src="readme_images/react.png" alt="node" style="width:200px;"/>
  <br />
  Download here:
  <br />
  https://en.reactjs.org
  </p>
  
## <span style="color: rgb(26, 99, 169);">**Hardware**</span>
- Node MCU ESP8266
  <p style="text-align: center;">
  <img src="readme_images/node.png" alt="node" style="width:200px;"/>
  <br />
  Setting up your ESP8266:
  <br />
  https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/
  <br />
  Arduino ESP8266 Pinouts:
  <br />
  https://esp8266-shop.com/esp8266-guide/esp8266-nodemcu-pinout/
  </p>
  
- Sound sensor
  <p style="text-align: center;">
  <img src="readme_images/modulo-sensor-ruido-sonido.png" alt="node" style="width:200px;"/>
  <br />
  Testing the Sound Sensor:
  <br />
  https://randomnerdtutorials.com/guide-for-microphone-sound-sensor-with-arduino/
  <br />
  Datasheet:
  <br />
  https://cdn.awsli.com.br/945/945993/arquivos/sound%20sensor%20module.pdf
  </p>
  
- Movement sensor
  <p style="text-align: center;">
  <img src="readme_images/motion.png" alt="node" style="width:200px;"/>
  <br />
  Testing the Motion Sensor:
  <br />
  https://randomnerdtutorials.com/arduino-with-pir-motion-sensor/
  <br />
  Datasheet:
  <br />
  https://www.epitran.it/ebayDrive/datasheet/44.pdf
  </p>
  
- Debbuging:
  <p style="text-align: center;">
  Failed to connect to ESP32: Timed out waiting for packet header:
  <br />
  https://www.arduino.cc/en/software](https://randomnerdtutorials.com/?s=+Timed+out+waiting+for+packet+header)
  </p>

## <span style="color: rgb(26, 99, 169);">**Data Base**</span>
 - Script:
   <p style = "text-align: center;">
     CREATE TABLE salon(
        salon_id INT NOT NULL PRIMARY KEY,
        capacidad INT,
        imagen TEXT
    );

    CREATE TABLE OCUPADO(
      salon_id INT NOT NULL,
        estado INT NOT NULL,
        hora TIME NOT NULL,
        fecha DATE NOT NULL,
        luz INT,
        PRIMARY KEY(estado, hora, fecha)
    );

    ALTER TABLE OCUPADO
    ADD FOREIGN KEY (salon_id) REFERENCES SALON(salon_id);

   </p>
   
 - Connection from Node MCU to Data Base:
   <p style="text-align: center;">
     This is where the Node.js server comes into play. Proceed if downloaded.
   </p>
 
 - From NODE MCU to server:
   <p style="text-align: center;">
     In the arduino code, once certain specifications are reached, the NodeMCU will send a data string to the server, this is in the for of
    </br>
        - If there is both sound and movement, and the lights are on. Sends to server classrooom id (3101), status (1) and light status (1). </br>
        - If there is both sound and movement, and the lights are off. Sends to server classroom id (3101), status (1) and light status (0). </br>
        - If there no sound or no movement, and the lights are on. Sends to server classroom id (3101), status (0) and light status (1). </br>
        - In any other case, sends to server classroom id (3101), status (0) ad light status (0).
     
     Remember from Hardware explanation that the status of classroom is marked as 'occupied' (with 1) only when it detects both sound and movement.
     What this part of the code does is send a POST request for the addition of the data string to the Data Base.
     
 Code for connexion, alongside its elxanation in commentry is in the following direction.
 code_server/index.js

  </p>
  
 - From Server to Data Base:
   <p>
       Once the POST request is sent, the js document sets the connection to the database and executes the querry to insert the values sent from the Node MCU. </br>
       Note that the NodeMCU does not send time and date, this is set in the JS code. </br>
       The code for this, along with its explanation in comments is available in the following rout: </br>
       iot_project/code_server/index.js /
       
  </p> 
  
## <span style="color: rgb(26, 99, 169);">**Web Page**</span>

