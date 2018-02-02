#include "Map.h"

Map::Map(size_t width, size_t height, const std::vector<Path>& paths) {
    // TODO: Implement this
}

Map::Map(const std::vector<std::vector<Cell>>& cells, const std::vector<Path>& paths) {
    // TODO: Implement this
}

void Map::set_width(size_t width) {
    // TODO: Implement this
}

void Map::set_height(size_t height) {
    // TODO: Implement this
}

void Map::set_cells(const std::vector<std::vector<Cell>>& cells) {
    // TODO: Implement this
}

void Map::set_my_units(const std::vector<Unit>& my_units) {
    // TODO: Implement this
}

void Map::set_enemy_units(const std::vector<Unit>& enemy_units) {
    // TODO: Implement this
}

void Map::set_my_towers(const std::vector<Tower>& my_towers) {
    // TODO: Implement this
}

void Map::set_visible_enemy_towers(const std::vector<Tower>& visible_enemy_towers) {
    // TODO: Implement this
}

void Map::set_paths(const std::vector<Path>& paths) {
    // TODO: Implement this
}

size_t Map::get_width() const {
    // TODO: Implement this
}

size_t Map::get_height() const {
    // TODO: Implement this
}

std::vector<std::vector<Cell>>& Map::get_cells() {
    // TODO: Implement this
}

const std::vector<std::vector<Cell>>& Map::get_cells() const {
    // TODO: Implement this
}

std::vector<std::shared_ptr<Unit>>& Map::get_my_units() {
    // TODO: Implement this
}

std::vector<std::shared_ptr<const Unit>> Map::get_my_units() const {
    // TODO: Implement this
}

std::vector<std::shared_ptr<Unit>>& Map::get_enemy_units() {
    // TODO: Implement this
}

std::vector<std::shared_ptr<const Unit>> Map::get_enemy_units() const {
    // TODO: Implement this
}

std::vector<std::shared_ptr<Tower>>& Map::get_my_towers() {
    // TODO: Implement this
}

std::vector<std::shared_ptr<const Tower>> Map::get_my_towers() const {
    // TODO: Implement this
}

std::vector<std::shared_ptr<Tower>>& Map::get_visible_enemy_towers() {
    // TODO: Implement this
}

std::vector<std::shared_ptr<const Tower>> Map::get_visible_enemy_towers() const {
    // TODO: Implement this
}

std::vector<Path>& Map::get_paths() {
    // TODO: Implement this
}

const std::vector<Path>& Map::get_paths() const {
    // TODO: Implement this
}
