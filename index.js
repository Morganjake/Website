const express = require('express');
const app = express();
const port = 4000;

app.use(express.static('app/public'));
app.use(express.json());

app.set("view engine", "ejs")
app.set("views", "app/views")

app.get('/', (req, res) => {
    res.send('Hello!');
});

app.get('/code', (req, res) => {
    res.render("code")
});

app.get('/write-ups/:topic/:algorithm', (req, res) => {
    const { topic, algorithm } = req.params;
    const algorithms = require("./data/algorithms/algorithms.json")
    res.render("write-ups", { algorithms: algorithms, topic: topic, algorithm: algorithm })
});

app.post('/api/submit', (req, res) => {
    const { text } = req.body;
    console.log('Received:', text);
    res.json({ ok: true });
});

app.listen(port, () => {
    console.log(`App listening at ${port}`);
});