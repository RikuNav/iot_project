const express = require('express');
const mysql = require('mysql');
const { readFile } = require('fs');
const { networkInterfaces } = require('os');
const app = express();
const cors = require('cors');

app.use(cors());

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
    password: 'root',             // Contraseña de usuario
    database: '4bits'               // Nombre de la base de datos
});

// Se conecta a la base de datos, si hay un error detiene la ejecución del programa
db.connect((err) => {
    if(err) throw err;
});

// Busca interfaces de red e imprime la dirección ip local
console.log('Server hosted on:')
networkInterfaces()['Wi-Fi'].forEach((netInt) => {
    if(netInt.family == 'IPv4')
        console.log(netInt.address);
})

// Maneja la ruta base en GET, devuelve el html de la página principal 
app.get('/', (req, res) => {
    console.log(req.query)
    if(!(req.query.cr))
    {
        readFile('./index.html', 'utf-8', (err, html) => {
            if(err) {
                res.status(500).send('Server error');
            }
            res.send(html);
    });
    }
    else 
    {
        db.query(`SELECT estado, luz FROM ocupado WHERE salon_id = ${req.query.cr} ORDER BY fecha DESC, hora DESC LIMIT 1;`, (err, result) => {
            if(err) throw err;
            console.log(result);
            res.send(result);
        });
    }
});

app.get('/data', (req, res) => {
    db.query(`SELECT * FROM ocupado`, (err, result) => {
        if(err)
            res.send('NULL');
        else 
            res.send(result);
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
    
    let id_salon = req.body.salon_id;
    let ocupado = req.body.estado;
    let time = new Date(Date.now()).toISOString();
    let date = time.split('T')[0];
    let hour = time.split('T')[1].split('.')[0];
    let querr = `INSERT INTO ocupado (salon_id, estado, fecha, hora, luz) VALUES (${id_salon},${ocupado},'${date}','${hour}', ${req.body.luz})`;
    console.log(querr);
    db.query(querr, (err, result) => {
        if(err) {
            console.log(err);
            //Hacer cosas si no se puede añadir a la base de datos
        } else {
            console.log(result);
        }
    });
    
   // Respuesta del servidor para el NodeMCU
    res.send('Funcio');
});

// Escucha el tráfico que llegue a localhost:3000
app.listen(process.env.PORT || 3000, () => console.log('App available at http://localhost:3000/'));
