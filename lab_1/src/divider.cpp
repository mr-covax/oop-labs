int get_min_divs(const int w, const int h) {
    if (w < 1 || h < 1)
        return 0;

    return (w - 1) + (h - 1);
}