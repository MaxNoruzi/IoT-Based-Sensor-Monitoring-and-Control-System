const express = require('express');
const axios = require('axios');

const app = express();
app.use(express.json()); // Middleware to parse JSON bodies

const port = 3000;
const controlNodeAddress = 'DesiredIp';

app.post('/sensor-data', async (req, res) => {
    const { temperature, light, isCardDetected } = req.body;

    console.log(`Temperature: ${temperature} C, Light: ${light} Lux, Card Detected: ${isCardDetected}`);

    const promises = [];

    const lightPath = light < 400 ? 'light-on' : 'light-off';
    promises.push(axios.get(`${controlNodeAddress}/${lightPath}`));

    if (isCardDetected) {
        promises.push(axios.get(`${controlNodeAddress}/buzzer-off`));
    }

    await Promise.all(promises);

    res.json({ message: 'Data received successfully' });
});

app.listen(port, () => {
    console.log(`Server listening at http://localhost:${port}`);
});

// Error handling Middleware
app.use((err, req, res, next) => {
    console.error(err.stack);
    res.status(500).send('Something broke!');
});
