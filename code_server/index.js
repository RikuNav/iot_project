const express = require('express');
const mysql = require('mysql');
const { readFile } = require('fs');
const { networkInterfaces } = require('os');
const app = express();

// Declaraciones de ayuda para leer datos enviados como JSON y texto en http
app.use(express.json());
app.use(express.text());

// Ruta para archivos estáticos 
// "todo archivo que no se encuentre se va a buscar en este directorio"
app.use(express.static('../webPage'));

// Crea la conección con la base de datos (no la conecta todavía)
const db = mysql.createConnection({
    host: 'localhost',            // Dónde está hosteada
    user: 'root',                 // Nombre de usuario
    password: '',             // Contraseña de usuario
    database: 'Iot'               // Nombre de la base de datos
});

// Se conecta a la base de datos, si hay un error detiene la ejecución del programa
db.connect((err) => {
    if(err) throw err;
});

// Querry de prueba, imprime el resultado como los regresa mysql
db.query('SELECT * FROM profesor', (err, res) => {
    if(err) throw err;
    console.log(res);
});

// Busca interfaces de red e imprime la dirección ip local
console.log('Server hosted on:')
networkInterfaces()['Wi-Fi'].forEach((netInt) => {
    if(netInt.family == 'IPv4')
        console.log(netInt.address);
})

// Maneja la ruta base en GET, devuelve el html de la página principal 
app.get('/', (req, res) => {
    readFile('./index.html', 'utf-8', (err, html) => {
        if(err) {
            res.status(500).send('Server error');
        }
        res.send(html);
    });
});

// Maneja la ruta /api, devuelve el estado del servidor y la base de datos
app.get('/api', (req, res) => {
    console.log('llamada del NodeMCU');
    // Envia el estado del servidor y la base de datos "Aún no hace mucho"
    res.send(JSON.stringify( { server:'ok', database: 'ok' } ));
});

// Escucha las request de POST en la ruta /api toma los datos y los añade a la base de datos
app.post('/api', (req, res) => {
    console.log(req.body);
    // Cuando sepamos cual va a ser el formato con los datos que nos va a mandar el nodeMCU
    // los pasamos al INSERT INTO de la tabla de nuestra base de datos correspondiente
    /*
    let post = { id: 5, nombres: 'Juan', aPaterno: 'López', aMaterno: 'Castro', fNacimiento: '1999-01-01'};
    db.query('INSERT INTO profesor SET ?', post, (err, result) => {
        if(err) {
            console.log(err);
            //Hacer cosas si no se puede añadir a la base de datos
        } else {
            console.log(result);
        }
    });
    */
   // Respuesta del servidor para el NodeMCU
    res.send('Funcio');
});

// Escucha el tráfico que llegue a localhost:3000
app.listen(process.env.PORT || 3000, () => console.log('App available at http://localhost:3000/'));
