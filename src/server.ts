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

// Iniciamos el servidor en el puerto 3000
serve(app, () => {
  console.log("Servidor corriendo en http://172.20.10.3:3000")
}) 