use serde::{Deserialize, Serialize};
use sqlx::{FromRow, Pool, Postgres};

#[derive(Debug, Clone, Copy, PartialEq)]
pub struct Point {
    pub x: f64,
    pub y: f64,
}

impl Point {
    pub fn new(x: f64, y: f64) -> Self {
        Point { x, y }
    }

    pub fn distance(&self, other: &Point) -> f64 {
        ((self.x - other.x).powi(2) + (self.y - other.y).powi(2)).sqrt()
    }
}

#[derive(Debug, Clone, Deserialize, Serialize, FromRow)]
pub struct Local {
    pub name:        String,
    pub lat:         f64,
    pub long:        f64,
    pub img_path:    Option<String>,
    pub description: Option<String>,
    pub ty:          Option<String>,
    pub display_name:Option<String>,
}

impl Local {
    pub fn point(&self) -> Point {
        Point::new(self.lat, self.long)
    }
}

#[derive(Debug)]
pub struct AppState {
    db: Pool<Postgres>,
}

impl AppState {
    pub fn new(db: Pool<Postgres>) -> Self {
        Self { db }
    }

    pub fn db(&self) -> &Pool<Postgres> {
        &self.db
    }
}