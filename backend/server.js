const express = require('express');
const bodyParser = require('body-parser');

const app = express();
app.use(bodyParser.json());

// Simulasi database UID yang valid
const validUIDs = ["65fcc11", "123abc", "456def"];

// Endpoint untuk cek UID
app.get('/checkUID', (req, res) => {
  const uid = req.query.uid;

  if (validUIDs.includes(uid)) {
    return res.status(200).json({ status: 'UID_VALID' });
  } else {
    return res.status(404).json({ status: 'UID_INVALID' });
  }
});

const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
  console.log(`Server running on port ${PORT}`);
});
