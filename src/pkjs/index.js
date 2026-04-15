var HTML = String.raw`
<!doctype html>
<html>
  <head>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
      body {
        font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", sans-serif;
        margin: 0;
        background: #111;
        color: #f5f5f5;
      }
      main {
        max-width: 420px;
        margin: 0 auto;
        padding: 24px 18px 28px;
      }
      h1 {
        margin: 0 0 6px;
        font-size: 28px;
      }
      p {
        margin: 0 0 18px;
        color: #bdbdbd;
      }
      label {
        display: block;
        margin: 16px 0 8px;
        font-weight: 600;
      }
      select {
        font-size: 16px;
      }
      select {
        width: 100%;
        padding: 12px;
        border-radius: 10px;
        border: 1px solid #444;
        background: #1b1b1b;
        color: #fff;
      }
      button {
        width: 100%;
        margin-top: 24px;
        padding: 14px;
        border: 0;
        border-radius: 999px;
        background: #f5f5f5;
        color: #111;
        font-weight: 700;
        font-size: 16px;
      }
    </style>
  </head>
  <body>
    <main>
      <h1>Glyph Dial</h1>
      <p>Quiet monochrome analog typography for Pebble Time 2 and Round 2.</p>

      <label for="theme">Theme</label>
      <select id="theme">
        <option value="0">Night</option>
        <option value="1">Paper</option>
      </select>

      <button id="save">Save</button>
    </main>

    <script>
      const key = "glyph-dial-settings";
      const theme = document.getElementById("theme");

      try {
        const saved = JSON.parse(localStorage.getItem(key) || "{}");
        if (saved.theme !== undefined) theme.value = String(saved.theme);
      } catch (err) {
      }

      document.getElementById("save").addEventListener("click", function () {
        const payload = {
          THEME: Number(theme.value)
        };
        localStorage.setItem(key, JSON.stringify({
          theme: payload.THEME
        }));
        document.location = "pebblejs://close#" + encodeURIComponent(JSON.stringify(payload));
      });
    </script>
  </body>
</html>
`;

Pebble.addEventListener("showConfiguration", function () {
  Pebble.openURL("data:text/html;charset=utf-8," + encodeURIComponent(HTML));
});

Pebble.addEventListener("webviewclosed", function (e) {
  if (!e || !e.response || e.response === "CANCELLED") {
    return;
  }

  try {
    var payload = JSON.parse(decodeURIComponent(e.response));
    Pebble.sendAppMessage(payload);
  } catch (err) {
    console.log("Config parse failed", err);
  }
});
