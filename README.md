import pandas as pd
import numpy as np
from sklearn.metrics.pairwise import cosine_similarity
from sklearn.feature_extraction.text import CountVectorizer
from fuzzywuzzy import fuzz
from metaphone import doublemetaphone

# Load data from Excel
file_path = 'your_file.xlsx'  # Replace with your Excel file path
data = pd.read_excel(file_path)

# Preprocessing functions
def normalize_name(name):
    # Convert to lowercase, remove punctuations, extra spaces, etc.
    name = str(name).lower().replace(".", "").replace("-", "").replace(",", "")
    return name.strip()

def phonetic_encoding(name):
    # Using Double Metaphone for phonetic similarity
    encoded = doublemetaphone(name)
    return encoded[0] if encoded[0] else encoded[1]

# Similarity functions
def calculate_similarities(name1, name2):
    # Normalize names
    name1, name2 = normalize_name(name1), normalize_name(name2)
    
    # Phonetic similarity
    phonetic_sim = fuzz.ratio(phonetic_encoding(name1), phonetic_encoding(name2)) / 100.0
    
    # Edit distance similarity (Levenshtein)
    levenshtein_sim = fuzz.ratio(name1, name2) / 100.0
    
    # Jaro-Winkler similarity
    jaro_winkler_sim = fuzz.token_sort_ratio(name1, name2) / 100.0

    # Cosine similarity on character n-grams
    vectorizer = CountVectorizer(analyzer='char', ngram_range=(2, 3))
    ngram_matrix = vectorizer.fit_transform([name1, name2])
    cosine_sim = cosine_similarity(ngram_matrix[0:1], ngram_matrix[1:2])[0][0]
    
    # Weighted similarity score
    weighted_score = 0.3 * phonetic_sim + 0.3 * levenshtein_sim + 0.2 * jaro_winkler_sim + 0.2 * cosine_sim
    return weighted_score

# Matching function
def match_names_from_excel(data, threshold=0.75):
    results = []
    for _, row in data.iterrows():
        name1, name2 = row['Name1'], row['Name2']
        actual_label = row['Label']
        score = calculate_similarities(name1, name2)
        predicted_match = 1 if score >= threshold else 0
        results.append((name1, name2, score, predicted_match, actual_label))
    
    # Convert results to a DataFrame
    results_df = pd.DataFrame(results, columns=["Name1", "Name2", "Similarity Score", "Predicted Match", "Actual Label"])
    return results_df

# Run the matching
matched_df = match_names_from_excel(data, threshold=0.75)

# Display results
print("Matched Names:")
print(matched_df)

# Calculate accuracy if Label column exists
if 'Label' in matched_df.columns:
    accuracy = (matched_df['Predicted Match'] == matched_df['Actual Label']).mean() * 100
    print(f"Accuracy: {accuracy:.2f}%")
