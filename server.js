import express from "express"
import cors from "cors"
import axios from "axios"

const app = express()

app.use(cors())
app.use(express.json())

app.post("/chat", async (req, res) => {

try {

const user = req.body.message
const sensor = req.body.sensorData

const prompt = `
You are an indoor air quality assistant.

Sensor Data:
Temperature: ${sensor.temp} °C
CO2: ${sensor.co2} ppm
Oxygen: ${sensor.o2} %
VOC: ${sensor.voc} ppb

User Question: ${user}

Give short health advice.
`

const response = await axios.post("http://localhost:11434/api/generate",{

model: "llama3",
prompt: prompt,
stream: false

})

res.json({
reply: response.data.response
})

}

catch(error){

console.log(error)

res.json({
reply: "Local AI error"
})

}

})

app.listen(5000, () => {
console.log("Server running on port 5000")
})