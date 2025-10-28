const express = require("express");
const fs = require("fs");
const { execSync } = require("child_process");
const app = express();

app.use(express.static("public"));
app.use(express.json());

// API endpoint for spell checking
app.post("/check", (req, res) => {
  const word = req.body.word?.trim();
  if (!word) return res.json({ result: "⚠️ Please enter a word." });

  // Write the input
  fs.writeFileSync("input.txt", word);

  try {
    // Run the compiled C backend
    execSync("spell_checker.exe"); // use "spell_checker.exe" on Windows
    const output = fs.readFileSync("output.txt", "utf8");
    res.json({ result: output });
  } catch (err) {
    res.json({ result: "❌ Error executing spell checker." });
  }
});

const PORT = 3000;
app.listen(PORT, () => console.log(`🚀 Server running at http://localhost:${PORT}`));
