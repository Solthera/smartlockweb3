const express = require('express');
const { checkUID } = require('../controllers/uidController');
const router = express.Router();

router.post('/check', checkUID); // endpoint: /uid/check

module.exports = router;
