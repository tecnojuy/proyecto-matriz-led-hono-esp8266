import { serve } from "@hono/node-server"
import { Hono } from "hono"
import { cors } from "hono/cors"
import fs from 'node:fs'
import path from 'node:path'

const app = new Hono()
let ultimoMensaje = "" // Variable para almacenar el último mensaje

// Habilitamos CORS para permitir peticiones desde el frontend
app.use(cors())

// Servir el archivo index.html
app.get('/', async (c) => {
  const htmlPath = path.join(process.cwd(), 'public', 'index.html')
  const html = await fs.promises.readFile(htmlPath, 'utf-8')
  return c.html(html)
})

// Ruta para recibir el mensaje desde el frontend
app.post("/mensaje", async (c) => {
  const { mensaje } = await c.req.json()
  ultimoMensaje = mensaje // Guardamos el mensaje
  console.log("Mensaje recibido:", mensaje)
  return c.json({ success: true, mensaje })
})

// Ruta para que el ESP8266 obtenga el último mensaje
app.get("/mensaje", (c) => {
  return c.json({ mensaje: ultimoMensaje })
})

const PORT = Number(process.env.PORT) || 3000
const HOST = process.env.HOST || 'TU-IP-LOCAL'

// Iniciamos el servidor en el puerto especificado
serve({
  fetch: app.fetch,
  port: PORT
}, () => {
  console.log(`Servidor corriendo en http://${HOST}:${PORT}`)
}) 