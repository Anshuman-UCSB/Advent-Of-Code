/** @type {import('tailwindcss').Config} */
export default {
  content: [
    "./index.html",
    "./src/**/*.{js,ts,jsx,tsx}",
  ],
  theme: {
    extend: {
      colors: {
        AOCBackground: '#0f0f23',
        AOCText: '#00cc00',
      },
    },
  },
  plugins: [],
}

