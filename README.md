# TriacSoftStart ⚡️🌀

**Arranque progresivo de motores AC monofásicos usando Arduino + TRIAC**  
Controla el arranque de cargas como bombas de agua, suavizando el pico de corriente en el arranque, ideal para sistemas de suministro solares o limitados.

---

## 🧰 ¿Qué hace esta biblioteca?

Esta biblioteca te permite controlar **el momento en que se dispara un TRIAC** en cada semiciclo de corriente alterna.  
De esta manera, puedes arrancar un motor **de forma progresiva**, aumentando poco a poco el ángulo de conducción hasta llegar al ciclo completo. NO ES UN VARIADOR MONOFASICO.

---

## 🎯 Características

- 🕒 Rampa de retardo ajustable
- 🔥 Pulso controlado para activar el MOC3021 (o similar)
- 📉 Evita picos de arranque en bombas o motores
- 🧠 Pin de control para reinicio o apagado total
- 💡 LED que indica si está en rampa o en estado estable

---

## 🧪 Aplicaciones típicas

✅ Bombas de agua
✅ Extractores o compresores
✅ Arranque controlado en sistemas solares 
✅ Control de cargas inductivas medianas


