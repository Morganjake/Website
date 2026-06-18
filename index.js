let interfaceWithC = require("./backend/codingLanguage/interfaceWithC")

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
	const updateLog = require("./data/code/updateLog.json")
	res.render("code", { updateLog: updateLog.updates})
});

app.post('/api/submit', async (req, res) => {
	const { text } = req.body;
	let ans = await interfaceWithC.interfaceWithC(text)
	res.json(ans);
});

app.listen(port, () => {
	console.log(`App listening at ${port}`);
});