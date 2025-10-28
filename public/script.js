async function checkSpelling() {
  const word = document.getElementById("wordInput").value.trim();
  const resultBox = document.getElementById("result");

  if (!word) {
    resultBox.textContent = "⚠️ Please enter a word.";
    return;
  }

  const response = await fetch("/check", {
    method: "POST",
    headers: { "Content-Type": "application/json" },
    body: JSON.stringify({ word })
  });

  const data = await response.json();
  resultBox.textContent = data.result;
}
