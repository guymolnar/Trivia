import requests
import sqlite3
import html
import random

DB_PATH = "trivia.db"
API_URL = "https://opentdb.com/api.php?amount=10&type=multiple"

def populate_questions():
    response = requests.get(API_URL)
    data = response.json()

    conn = sqlite3.connect(DB_PATH)
    cursor = conn.cursor()

    for item in data["results"]:
        question = html.unescape(item["question"])
        correct = html.unescape(item["correct_answer"])
        wrongs = [html.unescape(a) for a in item["incorrect_answers"]]

        # mix correct answer into random position
        answers = wrongs + [correct]
        random.shuffle(answers)
        correct_id = answers.index(correct) + 1  # 1-based index

        cursor.execute("""
            INSERT INTO questions (question, answer1, answer2, answer3, answer4, correctAnswerId)
            VALUES (?, ?, ?, ?, ?, ?)
        """, (question, answers[0], answers[1], answers[2], answers[3], correct_id))

    conn.commit()
    conn.close()
    print("Inserted 10 questions successfully")

if __name__ == "__main__":
    populate_questions()