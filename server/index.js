const express = require('express');
const app = express();
const cors = require('cors');

app.use(cors());
app.use(express.json());

app.get('/', (req, res) => {
  res.send('SmartLock Backend is running!');
});

app.get('/checkUID', (req, res) => {
  const { uid } = req.query;
  // logika pengecekan UID dari blockchain bisa masuk sini
  if (uid === "65fcc11") {
    return res.send("UID_VALID");
  } else {
    return res.status(403).send("UID_INVALID");
  }
});

const PORT = process.env.PORT || 3000;
app.listen(PORT, () => console.log(`Server running on port ${PORT}`));
