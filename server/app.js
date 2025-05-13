require('dotenv').config();
const express = require('express');
const uidRoutes = require('./routes/uid');
const app = express();

app.use(express.json());
app.use('/uid', uidRoutes);

const PORT = process.env.PORT || 3000;
app.listen(PORT, () => console.log(`Server running on port ${PORT}`));
