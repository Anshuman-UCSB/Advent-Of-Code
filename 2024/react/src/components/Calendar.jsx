export default function Calendar() {
    const CURRENT_DAY = 1;
    return (
        <div className="w-50% h-full grid grid-cols-5 gap-6">
            {Array.from({ length: 25 }).map((_, index) => (
                <div key={index} className="bg-AOCText w-10% aspect-square text-center 
                flex items-center justify-center font-bold text-[10vw]">{index + 1}</div>
            ))}
        </div>
    )
}

