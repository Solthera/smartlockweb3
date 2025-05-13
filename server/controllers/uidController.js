const { ethers } = require('ethers');
const abi = require('../abi/SmartLock.json');

const contractAddress = process.env.CONTRACT_ADDRESS;
const provider = new ethers.JsonRpcProvider(process.env.RPC_URL);
const contract = new ethers.Contract(contractAddress, abi, provider);

exports.checkUID = async (req, res) => {
  const { uid } = req.body;
  try {
    const isRegistered = await contract.isUIDRegistered(uid); // asumsi ada fungsi ini
    res.json({ access: isRegistered ? 'granted' : 'denied' });
  } catch (err) {
    console.error(err);
    res.status(500).json({ error: 'Blockchain check failed' });
  }
};
